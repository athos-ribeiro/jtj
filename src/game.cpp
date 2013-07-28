#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "enemy.h"
#include "box.h"
#include "sdlutil.h"
#include <cstdlib>
#include "SDL/SDL_ttf.h"
#include "scorescreen.h"
#include <stdio.h>

using namespace std;
/* Structure for loaded sounds. */
typedef struct sound_s {
    Uint8 *samples;     /* raw PCM sample data */
    Uint32 length;      /* size of sound data in bytes */
} sound_t, *sound_p;

/* Structure for a currently playing sound. */
typedef struct playing_s {
    int active;                 /* 1 if this sound should be played */
    sound_p sound;              /* sound data to play */
    Uint32 position;            /* current position in the sound buffer */
} playing_t, *playing_p;

/* Array for all active sound effects. */
#define MAX_PLAYING_SOUNDS      10
playing_t playing[MAX_PLAYING_SOUNDS];

/* The higher this is, the louder each currently playing sound will be.
   However, high values may cause distortion if too many sounds are
   playing. Experiment with this. */
#define VOLUME_PER_SOUND        SDL_MIX_MAXVOLUME / 2

/* Audio format specifications. */
SDL_AudioSpec desired, obtained;

/* Our loaded sounds and their formats. */
sound_t initScreenSound;

void AudioCallback(void *user_data, Uint8 *audio, int length)
{
    int i;

    /* Avoid compiler warning. */
//    user_data += 0;

    /* Clear the audio buffer so we can mix samples into it. */
    memset(audio, 0, length);

    /* Mix in each sound. */
    for (i = 0; i < MAX_PLAYING_SOUNDS; i++) {
    if (playing[i].active) {
        Uint8 *sound_buf;
        Uint32 sound_len;

        /* Locate this sound's current buffer position. */
        sound_buf = playing[i].sound->samples;
        sound_buf += playing[i].position;

        /* Determine the number of samples to mix. */
        if ((playing[i].position + length) > playing[i].sound->length) {
        sound_len = playing[i].sound->length - playing[i].position;
        } else {
        sound_len = length;
        }

        /* Mix this sound into the stream. */
        SDL_MixAudio(audio, sound_buf, sound_len, VOLUME_PER_SOUND);

        /* Update the sound buffer's position. */
        playing[i].position += length;

        /* Have we reached the end of the sound? */
        if (playing[i].position >= playing[i].sound->length) {
        playing[i].active = 0;  /* mark it inactive */
        }
    }
    }
}


/* This function loads a sound with SDL_LoadWAV and converts
   it to the specified sample format. Returns 0 on success
   and 1 on failure. */
int LoadAndConvertSound(char *filename, SDL_AudioSpec *spec,
            sound_p sound)
{
    SDL_AudioCVT cvt;           /* audio format conversion structure */
    SDL_AudioSpec loaded;       /* format of the loaded data */
    Uint8 *new_buf;

    /* Load the WAV file in its original sample format. */
    if (SDL_LoadWAV(filename,
            &loaded, &sound->samples, &sound->length) == NULL) {
    printf("Unable to load sound: %s\n", SDL_GetError());
    return 1;
    }

    /* Build a conversion structure for converting the samples.
       This structure contains the data SDL needs to quickly
       convert between sample formats. */
    if (SDL_BuildAudioCVT(&cvt, loaded.format,
              loaded.channels,
              loaded.freq,
              spec->format, spec->channels, spec->freq) < 0) {
    printf("Unable to convert sound: %s\n", SDL_GetError());
    return 1;
    }

    /* Since converting PCM samples can result in more data
       (for instance, converting 8-bit mono to 16-bit stereo),
       we need to allocate a new buffer for the converted data.
       Fortunately SDL_BuildAudioCVT supplied the necessary
       information. */
    cvt.len = sound->length;
    new_buf = (Uint8 *) malloc(cvt.len * cvt.len_mult);
    if (new_buf == NULL) {
    printf("Memory allocation failed.\n");
    SDL_FreeWAV(sound->samples);
    return 1;
    }

    /* Copy the sound samples into the new buffer. */
    memcpy(new_buf, sound->samples, sound->length);

    /* Perform the conversion on the new buffer. */
    cvt.buf = new_buf;
    if (SDL_ConvertAudio(&cvt) < 0) {
    printf("Audio conversion error: %s\n", SDL_GetError());
    free(new_buf);
    SDL_FreeWAV(sound->samples);
    return 1;
    }

    /* Swap the converted data for the original. */
    SDL_FreeWAV(sound->samples);
    sound->samples = new_buf;
    sound->length = sound->length * cvt.len_mult;

    /* Success! */
    printf("'%s' was loaded and converted successfully.\n", filename);
    return 0;
}


/* Removes all currently playing sounds. */
void ClearPlayingSounds(void)
{
    int i;

    for (i = 0; i < MAX_PLAYING_SOUNDS; i++) {
    playing[i].active = 0;
    }
}

/* Adds a sound to the list of currently playing sounds.
   AudioCallback will start mixing this sound into the stream
   the next time it is called (probably in a fraction of a second). */
int PlaySound(sound_p sound)
{
    int i;

    /* Find an empty slot for this sound. */
    for (i = 0; i < MAX_PLAYING_SOUNDS; i++) {
    if (playing[i].active == 0)
        break;
    }

    /* Report failure if there were no free slots. */
    if (i == MAX_PLAYING_SOUNDS)
    return 1;

    /* The 'playing' structures are accessed by the audio callback,
       so we should obtain a lock before we access them. */
    SDL_LockAudio();
    playing[i].active = 1;
    playing[i].sound = sound;
    playing[i].position = 0;
    SDL_UnlockAudio();

    return 0;
}

void Game::initGUI() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init ();

    SDL_WM_SetCaption("Jack, The Janitor", NULL);
    SDL_WM_SetIcon(IMG_Load("resources/Logo_WareHouse_64x64.png"), NULL);
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
    return;
}

void Game::closeGUI() {
    SDL_CloseAudio ();
    TTF_Quit ();
    SDL_Quit();
    return;
}

void Game::loadCommonResources() {
    score = new ScoreScreen();

    /* Open the audio device. The sound driver will try to give us
    the requested format, but it might not succeed. The 'obtained'
    structure will be filled in with the actual format data. */
    desired.freq = 44100;   /* desired output sample rate */
    desired.format = AUDIO_S16; /* request signed 16-bit samples */
    desired.samples = 4096; /* this is more or less discretionary */
    desired.channels = 2;   /* ask for stereo */
    desired.callback = AudioCallback;
    desired.userdata = NULL;    /* we don't need this */
    if (SDL_OpenAudio(&desired, &obtained) < 0) {
    printf("Unable to open audio device: %s\n", SDL_GetError());
    return ;
    }

    /* Load our sound files and convert them to the sound card's format. */
    if (LoadAndConvertSound("resources/init_screen.wav", &obtained, &initScreenSound) != 0) {
    printf("Unable to load sound.\n");
    return ;
    }

    return;
}

void Game::releaseCommonResources() {
    return;
}

void Game::loadProfile() {
    return;
}

void Game::saveProfile() {
    return;
}

void Game::updateTimeStep() {
    frameTime.start();
    return;
}

void Game::handle_event_keydown (SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case (SDLK_ESCAPE):
            this->quitLevel = true;
            break;

        case (SDLK_w):
            if(jack->jumping == true) {
                break;
            }
            jack->verticalSpeed = -10;
            jack->jumping = true;
            break;

        case (SDLK_a):
            jack->pushMove(-3);
            break;

        case (SDLK_s):
            break;

        case (SDLK_q):
            cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
            this->gameOver = true;
            break;

        case (SDLK_d):
            jack->pushMove(3);
            break;

        case (SDLK_p):
            if (this->pauseLevel == true) {
                this->pauseLevel = false;
            }
            else {
                this->pauseLevel = true;
            }
            break;

        default:
            break;
    }
}

void Game::handle_event_keyup (SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case (SDLK_a):
            jack->popMove(-3);
            break;

        case (SDLK_d):
            jack->popMove(3);
            break;

        default:
            break;
    }
}

void Game::handle_event_mouse_button_up (SDL_Event& event) {
    switch (event.button.button) {

    case SDL_BUTTON_LEFT:
//      printf("Posicao onde o botao foi liberado: (%d, %d)\n", event.button.x, event.button.y);
        break;

    default:
        break;
    }

    return;
}


void Game::handle_event_mouse_button_down (SDL_Event& event) {
    switch (event.button.button) {

    case SDL_BUTTON_LEFT:
        break;

    case SDL_BUTTON_RIGHT:
        score->popBox();
        break;

    default:
        break;
    }

    return;
}

void Game::handle_event_type (SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        this->quitLevel = true;
        break;

    case SDL_KEYDOWN:
        handle_event_keydown (event);
        break;

    case SDL_KEYUP:
        handle_event_keyup (event);
        break;

    case SDL_MOUSEBUTTONDOWN:
        handle_event_mouse_button_down (event);
        break;

    case SDL_MOUSEBUTTONUP:
        handle_event_mouse_button_up (event);
        break;

    default:
        break;
    }
}

void Game::handleEvents() {
    while (SDL_PollEvent (&event)) {
        handle_event_type (event);
    }
    return;
}

void Game::runAI() {
    for(unsigned int i = 0; i < level->enemies.size(); i++) {
        level->enemies[i]->throwBox(level->boxes);
        level->enemies[i]->move();
    }
    return;
}

bool checkColision (Jack* jack, std::vector<Box*> boxes) {

    for (unsigned int i = 0; i < boxes.size(); ++i)
    {
//        cout << "Box " << i << "(" << boxes[i]->getPositionX() << "," << boxes[i]->getPositionY() << ")\t";
//        cout << "(" << boxes[i]->getPositionX() + 38 << "," << boxes[i]->getPositionY() + 38 << ")" << endl;

		int jackRight = jack->getXPosition() + Box::BOX_WIDTH;
		int jackLeft = jack->getXPosition();
		int jackTop = jack->getYPosition();
		int jackBottom = jack->getYPosition()+Jack::JACK_HEIGHT;
		int boxRight =boxes[i]->getPositionX() + Box::BOX_HEIGHT;
		int boxLeft = boxes[i]->getPositionX();
		int boxTop = boxes[i]->getPositionY();
		int boxBottom = boxes[i]->getPositionY()+Box::BOX_HEIGHT;

		if(((boxLeft < jackLeft && jackRight < boxRight) && (boxTop < jackTop && jackTop < boxBottom)) ||
				((jackLeft < boxLeft && boxLeft < jackRight) && (jackTop < boxTop && boxTop < jackBottom)))
		 {

			cout << "Jack: ("<< jackLeft <<", " << jackRight << ") e ("<< jackTop <<", " << jackBottom << endl;
			cout << "Box: ("<< boxLeft <<", " << boxRight << ") e ("<< boxTop <<", " << boxBottom << endl;

			return true;
		}
    }

    return false;
}

void Game::runPhysics() {

	cout << "Checando colisão" << endl;
    if (checkColision (jack, level->boxes)) {
        jack->die();
    }
	cout << "Colisão checada." << endl;

//    cout << "Jogador (" << jack->getXPosition() << "," << jack->getYPosition() << ")" << endl;
    //notice that when the game restarts, another box is pushed into the array
	cout << "Derrubando caixas" << endl;
    for(unsigned int i = 0; i < level->boxes.size(); i++) {
        if(level->boxes[i]->used == true) {
            level->boxes[i]->fall(level->grid);
        }
    }

    int xinit = Level::LEVEL_X_OFFSET;
    //int yinit=Level::LEVEL_Y_OFFSET;
    int xrange=Level::LEVEL_WIDTH+Level::LEVEL_X_OFFSET;
    //int yfinal=Level::LEVEL_HEIGHT-Level::LEVEL_Y_OFFSET;
    int jackposx = (jack->getXPosition()-Level::LEVEL_X_OFFSET)/38;
    int jackposy = (jack->getYPosition()-Level::LEVEL_Y_OFFSET + Jack::JACK_HEIGHT+19)/38;

    //Looking for the first box before Jack
	cout << "Procurando pela caixa móvel antes do Jack" << endl;
    int boxMobileBeforeJack=-1;
    int boxMobileAfterJack=-1;
    for(int i=jackposx;i>=0;i--) {
		if((level->grid[i].size()+jackposy)>=12) {
            xinit=Level::LEVEL_X_OFFSET+ (i+1)*38;
            if((level->grid[i].size()+jackposy)==12) {
                if(i>0){
                    if(level->grid[i-1].size()>=level->grid[i].size())
						break;
					else
						boxMobileBeforeJack = i;
                }
            }
            break;
        }
    }

	cout << "Procurando pela caixa móvel depois do Jack" << endl;
    //Looking for the first box after Jack
    for(int i=jackposx;i<12;i++) {
		if((level->grid[i].size()+jackposy)>=12) {
            xrange=Level::LEVEL_X_OFFSET+ (i)*38-xinit;
            if((level->grid[i].size()+jackposy)==12) {
                if(i<11){
                    if(level->grid[i+1].size()>=level->grid[i].size())
                       break;
					else
						boxMobileAfterJack = i;
                }
            }
            break;
        }
    }

    for (int i = 0; i < 12; ++i)
    {
//        cout << i << " " << level->grid[i] << endl;
        if (level->grid[i].size() > 7)
        {
            this->quitGame = true;
        }
    }


    int quantidadeDeCaixas = 0;
    for (int i = 0; i < 12; ++i)
    {
        if (level->grid[i].size() > 0)
        {
            quantidadeDeCaixas++;
        }
    }

    if (quantidadeDeCaixas == 12)
    {
		score->increaseScore(1000);
		if(jack->jumping != true) {
			jack->verticalSpeed = -10;
			jack->jumping = true;
		}
        for (int i = 0; i < 12; ++i)
        {
            cout << "LALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALA" << endl;
			Box* boxToDelete = level->grid[i].back();
			for(vector<Box*>::iterator it=level->boxes.begin();it!=level->boxes.end();it++) {
				if(*it==boxToDelete) {
                    //delete level->boxes.it;
                    Box* myBox = *it;
					level->boxes.erase(it);
                    myBox->used = false;
					break;
				}
			}
			level->grid[i].pop_back();
        }
    }

    if(xinit<Level::LEVEL_X_OFFSET)
        xinit=Level::LEVEL_X_OFFSET;
    if(xrange+xinit>(Level::LEVEL_WIDTH+Level::LEVEL_X_OFFSET))
        xrange = (Level::LEVEL_WIDTH+Level::LEVEL_X_OFFSET) -xinit;

	if(boxMobileBeforeJack!=-1) {
        cout << "Primeira caixa móvel antes de jack: " << boxMobileBeforeJack << endl;
		if(jack->getXPosition()==(((boxMobileBeforeJack+1)*Box::BOX_WIDTH)+Level::LEVEL_X_OFFSET)) {
			cout << "Colidiu com uma caixa a esquerda!!! forca: " << jack->strength << endl;
			if(jack->strength<10){
				jack->strength++;
			}
			if((jack->strength>=10)&&(jack->speed<0)) {
				Box* boxTransition = level->grid[boxMobileBeforeJack].back();
				boxTransition->x_position -= Box::BOX_WIDTH;
				level->grid[boxMobileBeforeJack].pop_back();
				boxTransition->lyingDown=false;
				boxTransition->fall(level->grid);
			}
			//level->grid[boxMobileBeforeJack-1].push_back(boxTransition);
		}
	}
	if(boxMobileAfterJack!=-1) {
        cout << "Primeira caixa móvel depois de jack: " << boxMobileAfterJack << endl;
		if((jack->getXPosition()+Jack::JACK_WIDTH)==(xrange+xinit)) {
			cout << "Colidiu com uma caixa a direta!!!" << endl;
			if(jack->strength<10){
				jack->strength++;
			}
			if((jack->strength>=10)&&(jack->speed>0)) {
				Box* boxTransitionRight = level->grid[boxMobileAfterJack].back();
				boxTransitionRight->x_position += Box::BOX_WIDTH;
				level->grid[boxMobileAfterJack].pop_back();
				boxTransitionRight->lyingDown=false;
				boxTransitionRight->fall(level->grid);
			}
		}
	}
	if(jack->speed==0){
			jack->strength=0;
	}
    cout << "Limite a direita do jack: " << xrange+xinit << endl;
    cout << "Limite a esquerda do jack: " << xinit << endl;
    jack->move(xinit, xrange, Level::LEVEL_Y_OFFSET, Level::LEVEL_HEIGHT);
    //cout << "Jack moveu" << endl;
    jack->jump(level);
    return;
}

void Game::update() {

    if (jack->isDead())
    {
        gameOvering();
    }
    if (score->getBox() < 0)
    {
        gameOver = true;
    }

    if (score->getScorePoints() > 99999)
    {
        gameOver = true;
    }

    if (pauseLevel == true) {
        pausingLevel();
    }
    if (isGameFinished())
    {
        gameOvering();
    }
    return;
}

void Game::recieveNetworkData() {
    return;
}

void Game::sendNetworkData() {
    return;
}

int Game::checkIfSkip() {
    if (frameTime.get_ticks() < FRAME_MILISECOND) {
        frameTime.waitDiff(FRAME_MILISECOND);
        return 0;
    }
    else {
        return 1;
    }
}

void Game::draw() {
    if(checkIfSkip() == 0) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        level->draw(this->screen);
        score->drawSelf(this->screen);
        SDL_Flip(this->screen);
    }
    return;
}

void Game::loadLevel() {
    level = new Level("resources/level_1.png");

    jack = new Jack("resources/jack_sprites.png");
    jack->setSpriteClips();
    level->addChild(jack);

    ifstream levelFile;
    string numberOfLevel;
    string numberOfBoxes;
    string numberOfEnemies;
    levelFile.open("resources/level_1");
    getline(levelFile, numberOfLevel);
    getline(levelFile, numberOfBoxes);
    getline(levelFile, numberOfEnemies);
    levelFile.close();

    for(int i = 0; i < atoi(numberOfBoxes.c_str()); i++) {
        Box* box = new Box("resources/box.png");
        level->boxes.push_back(box);
        level->addChild(box);
    }

    for(int i = 0; i < atoi(numberOfEnemies.c_str()); i++) {
        Enemy* enemy = new Enemy("resources/enemy_sprites.png");
        enemy->setSpriteClips();
        level->enemies.push_back(enemy);
        level->addChild(enemy);
    }
    //level->enemies[0]->throwBox(level->boxes);

    //Enemy* enemy = new Enemy("resources/enemy_1.png");
    //level->addChild(enemy);

    //boxTest = new Box("resources/box.png");
    //level->addChild(boxTest);
    //enemy->throwBox(boxTest, &level->boxes);

    score->boxes(atoi(numberOfBoxes.c_str()));
    score->scoring(100);

    return;
}

void Game::releaseLevel() {
    if(level) {
        delete level;
    }
    return;
}

bool Game::isGameFinished() {
    return this->quitGame;
}

bool Game::isLevelFinished() {
    return this->quitLevel;
}

void Game::initScreenDraw() {
    initScreen = new InitScreen("resources/backgroundinitscreen.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    initScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    initScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    initScreen->addChild(labelQuit);

    return;
}

void Game::pauseScreenDraw() {
	pauseScreen = new PauseScreen("resources/backgroundpausescreen.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    pauseScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    pauseScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    pauseScreen->addChild(labelQuit);

    return;
}

void Game::pauseScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;
    bool keyPressed = false;
    this->quitLevel = false;

    do {
        while (SDL_PollEvent (&event)) {
            switch (event.type) {
            case SDL_QUIT:
                this->quitLevel = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (labelPlay->wasClicked(event.button.x, event.button.y)) {
                        playButton = true;
                        this->quitLevel = false;
                        this->pauseLevel = false;
                    } else if (labelOptions->wasClicked(event.button.x, event.button.y)) {
                        optionsButton = true;
                    } else if (labelQuit->wasClicked(event.button.x, event.button.y)) {
                        this->quitLevel = true;
                        quitButton = true;
                    }
                    break;

                default:
                    break;
                }
                break;

            case SDL_KEYDOWN:
        	    switch (event.key.keysym.sym) {
				case (SDLK_p):
					keyPressed = true;
					this->pauseLevel = false;
				    break;

				default:
					break;
				}
				break;

            default:
                break;
            }
        }
        pauseScreen->draw(this->screen);
        SDL_Flip(this->screen);
    } while (keyPressed == false && playButton == false && optionsButton == false && quitButton == false);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    return ;
}

void Game::initScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;
    this->quitGame = false;
    this->quitLevel = false;
    this->pauseLevel = false;
    this->gameOver = false;

    do {
        while (SDL_PollEvent (&event)) {
            switch (event.type) {
            case SDL_QUIT:
                this->quitGame = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (labelPlay->wasClicked(event.button.x, event.button.y)) {
                        playButton = true;
                        this->quitLevel = false;
                    } else if (labelOptions->wasClicked(event.button.x, event.button.y)) {
                        optionsButton = true;
                    } else if (labelQuit->wasClicked(event.button.x, event.button.y)) {
                        this->quitGame = true;
                        quitButton = true;
                    }
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        initScreen->draw(this->screen);
        SDL_Flip(this->screen);
    } while (playButton == false && optionsButton == false && quitButton == false);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    return ;
}

void Game::init() {
    initGUI();
    loadCommonResources();

    FRAME_MILISECOND = 1000 / SCREEN_FPS;
    this->quitGame = false;
    this->quitLevel = false;
	this->pauseLevel = false;
	this->gameOver = false;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    return;
}

void Game::pausingLevel() {
	pauseScreenDraw();
    jack->popMove(3);
    jack->popMove(-3);
	pauseScreenLoop();

	return ;
}

void Game::initializingScreen() {
    /* Clear the list of playing sounds. */
    ClearPlayingSounds();

    /* SDL's audio is initially paused. Start it. */
    SDL_PauseAudio(0);

    PlaySound(&initScreenSound);

    initScreenDraw();
    initScreenLoop();

    SDL_PauseAudio(1);

    return ;
}
void Game::gameOverScreenDraw() {
	gameOverScreen = new GameOverScreen("resources/backgroundgameover.png");

    labelPlay = new Label("resources/startbutton.png", 483, 68);
    gameOverScreen->addChild(labelPlay);

    labelOptions = new Label("resources/optionsbutton.png", 483, 191);
    gameOverScreen->addChild(labelOptions);

    labelQuit = new Label("resources/exitbutton.png", 483, 314);
    gameOverScreen->addChild(labelQuit);

    return;
}

void Game::gameOverScreenLoop() {
    bool playButton = false;
    bool quitButton = false;
    bool optionsButton = false;
    this->quitGame = false;
    this->quitLevel = true;

    do {
        while (SDL_PollEvent (&event)) {
            switch (event.type) {
            case SDL_QUIT:
                this->quitLevel = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (labelPlay->wasClicked(event.button.x, event.button.y)) {
                        playButton = true;
                        this->quitGame = false;
                    } else if (labelOptions->wasClicked(event.button.x, event.button.y)) {
                        optionsButton = true;
                    } else if (labelQuit->wasClicked(event.button.x, event.button.y)) {
                        this->quitGame = true;
                        quitButton = true;
                    }
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        gameOverScreen->draw(this->screen);
        SDL_Flip(this->screen);
    } while (playButton == false && optionsButton == false && quitButton == false);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    return ;
}

void Game::gameOvering() {
    gameOverScreenDraw();
    jack->popMove(3);
    jack->popMove(-3);
    gameOverScreenLoop();

    return ;
}

void Game::shutdown() {
    SDL_LockAudio();

    free(initScreenSound.samples);
    SDL_UnlockAudio();
    closeGUI();
    return;
}

void Game::loop() {
    while(isGameFinished() == false) {
        initializingScreen();

        if (isGameFinished())
            break;
        loadLevel();
        while(isLevelFinished() == false) {
            updateTimeStep();
            recieveNetworkData();
            handleEvents();
            runAI();
            runPhysics();
            update();
            sendNetworkData();
            draw();
        }
        releaseLevel();
    }
    return;
}

