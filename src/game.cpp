#include <iostream>
#include "game.h"
#include "enemy.h"
#include "box.h"
#include "sdlutil.h"
#include <cstdlib>
#include "SDL/SDL_ttf.h"

using namespace std;
Box* box[6];

void Game::initGUI() {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init ();

    SDL_WM_SetCaption("Jack, The Janitor", NULL);
    SDL_WM_SetIcon(IMG_Load("resources/Logo_WareHouse_64x64.png"), NULL);
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
    return;
}

void Game::closeGUI() {
    TTF_Quit ();
    SDL_Quit();
    return;
}

void Game::loadCommonResources() {
    string scoreFontFileName = "resources/HanaleiRegular.ttf";
    int scoreFontSize = 30;
    scoreTextColor.r = 255;
    scoreTextColor.g = 255;
    scoreTextColor.b = 255;
    scoreFont = TTF_OpenFont (scoreFontFileName.c_str(), scoreFontSize);

    return;
}

void Game::releaseCommonResources() {
    TTF_CloseFont (scoreFont);
    SDL_FreeSurface (scoreMessage);
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
            //How about jack take the box and carry it with him?
//          this->quitLevel = true;
            break;

        case (SDLK_q):
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
//      printf("Posicao onde o botao foi apertado: (%d, %d)\n", event.button.x, event.button.y);
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
    return;
}

void Game::runPhysics() {

    int xinit = Level::LEVEL_X_OFFSET;
    int yinit;
    int xfinal;
    int yfinal;
    int jackposx = (jack->getXPosition()-Level::LEVEL_X_OFFSET)/38;
    int jackposy = (jack->getYPosition()-Level::LEVEL_Y_OFFSET)/38;
    cout << "Jack esta no grid " << jackposx << endl;
    for(int i=jackposx;i>=0;i--) {
        if(level->grid[i]!=0)
	{
		cout << "A caixa a esquerda esta no grid "<< i << endl;
		xinit=Level::LEVEL_X_OFFSET+ (i+1)*38;
		break;
	}
    }
    cout << "Limite a esquerda de Jack: " << xinit << endl;
    cout << "Posicao do Jack: " << jack->getXPosition() << endl;

    jack->move(xinit, Level::LEVEL_WIDTH, Level::LEVEL_Y_OFFSET, Level::LEVEL_HEIGHT);
    jack->jump(level);
    box[0]->fall(level);
    box[1]->fall(level);
    box[5]->fall(level);
    return;
}

void Game::update() {
    if (pauseLevel == true) {
        pausingLevel();
    }
    if (gameOver == true)
    {
        gameOvering();
    }
    scorePoints ++;
    sprintf(scoreString, "Score: %4d", scorePoints);
    scoreMessage = TTF_RenderText_Solid (scoreFont, scoreString, scoreTextColor);
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
        SDLUtil::applySurface (556, 50, scoreMessage, this->screen);
        SDL_Flip(this->screen);
    }
    return;
}

void Game::loadLevel() {
    level = new Level("resources/level_1.png");

    jack = new Jack("resources/jack.png");
    level->addChild(jack);

    Enemy* enemy = new Enemy("resources/enemy_1.png");
    level->addChild(enemy);

    for(int i = 0; i < 6; i++) {
        box[i] = new Box("resources/box.png");
    }
    box[0]->setPosition(Level::LEVEL_X_OFFSET, 250);
    box[1]->setPosition(Level::LEVEL_X_OFFSET + 10*38, 200);
    box[2]->setPosition(Level::LEVEL_X_OFFSET + 4*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38*2);
    box[3]->setPosition(Level::LEVEL_X_OFFSET + 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38*2);
    box[4]->setPosition(Level::LEVEL_X_OFFSET + 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38*3);
    box[5]->setPosition(Level::LEVEL_X_OFFSET, 100);
    for(int i = 0; i < 6; i++) {
        level->addChild(box[i]);
    }
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
    initScreenDraw();
    initScreenLoop();

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
                    } else if (labelOptions->wasClicked(event.button.x, event.button.y)) {
                        optionsButton = true;
                    } else if (labelQuit->wasClicked(event.button.x, event.button.y)) {
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
    closeGUI();
    return;
}

void Game::loop() {
    while(isGameFinished() == false) {
        initializingScreen();
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

