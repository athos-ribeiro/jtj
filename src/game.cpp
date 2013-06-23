#include <iostream>
#include "game.h"
#include "jack.h"
#include "level.h"
#include "enemy.h"
#include "box.h"
#include "timer.h"

using namespace std;

void Game::initGUI() {
    cout << "initializing GUI..." << endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("Jack, The Janitor", NULL);
    SDL_WM_SetIcon(IMG_Load("resources/Logo_WareHouse_64x64.png"), NULL);
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

    cout << "GUI started\n" << endl;
    return;
}

void Game::closeGUI() {
    cout << "closing GUI..." << endl;

    SDL_Quit();

    cout << "GUI closed\n" << endl;
    return;
}

void Game::loadCommonResources() {
    cout << "loading common resources..." << endl;
    cout << "common resources started\n" << endl;
    return;
}

void Game::releaseCommonResources() {
    cout << "releasing common resources..." << endl;
    cout << "common resources released\n" << endl;
    return;
}

void Game::loadProfile() {
    cout << "loading profile..." << endl;
    cout << "Profile loaded\n" << endl;
    return;
}

void Game::saveProfile() {
    cout << "saving profile..." << endl;
    cout << "Profile saved\n" << endl;
    return;
}

void Game::updateTimeStep() {
    cout << "Updating time step..." << endl;
    cout << "time step updated.\n" << endl;
    return;
}

void Game::handle_event_keydown (SDL_Event& event)
{
    switch (event.key.keysym.sym)
    {
    case (SDLK_ESCAPE):
        this->quitGame = true;
        this->quitLevel = true;
        break;

    case (SDLK_w):
        this->quitGame = true;
        this->quitLevel = true;
        break;

    case (SDLK_a):
        this->quitGame = true;
        this->quitLevel = true;
        break;

    case (SDLK_s):
        this->quitGame = true;
        this->quitLevel = true;
        break;

    case (SDLK_d):
        this->quitGame = true;
        this->quitLevel = true;
        break;

    default:
        break;
    }
}

void Game::handle_event_type (SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        this->quitGame = true;
        this->quitLevel = true;
        break;

    case SDL_KEYDOWN:
        handle_event_keydown (event);
        break;

    default:
        break;
    }
}

void Game::handleEvents() {
    cout << "handling events..." << endl;

    while (SDL_PollEvent (&event)) {
        handle_event_type (event);
    }

    cout << "events handled.\n" << endl;
    return;
}

void Game::runAI() {
    cout << "Running AI..." << endl;
    cout << "AI done.\n" << endl;
    return;
}

void Game::runPhysics() {
    cout << "Running physics..." << endl;
    cout << "Physics done.\n" << endl;
    return;
}

void Game::update() {
    cout << "Updating entities..." << endl;
    cout << "Entities updated.\n" << endl;
    return;
}

void Game::recieveNetworkData() {
    cout << "Sending and recieving packages..." << endl;
    cout << "Packages handled.\n" << endl;
    return;
}

void Game::sendNetworkData() {
    cout << "Sending and recieving packages..." << endl;
    cout << "Packages handled.\n" << endl;
    return;
}

void Game::draw() {
    cout << "Drawing..." << endl;

    level->draw(this->screen);
    SDL_Flip(this->screen);

    cout << "Drawing done.\n" << endl;
    return;
}

void Game::loadLevel() {
    cout << "Loading level..." << endl;

    level = new Level("resources/level_1.png");

    Jack* jack = new Jack("resources/jack.png");
    level->addChild(jack);

    Enemy* enemy = new Enemy("resources/enemy_1.png");
    level->addChild(enemy);

    Box* box[5];
    for(int i = 0; i < 5; i++) {
        box[i] = new Box("resources/box.png");
    }
    box[0]->setPosition(Level::LEVEL_X_OFFSET, 250);
    box[1]->setPosition(Level::LEVEL_X_OFFSET + 10*38, 200);
    box[2]->setPosition(Level::LEVEL_X_OFFSET + 4*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38);
    box[3]->setPosition(Level::LEVEL_X_OFFSET + 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38);
    box[4]->setPosition(Level::LEVEL_X_OFFSET + 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38*2);
    for(int i = 0; i < 5; i++) {
        level->addChild(box[i]);
    }

    cout << "Level loaded\n" << endl;
    return;
}

void Game::releaseLevel() {
    cout << "Releasing Level..." << endl;
    if(level) {
        delete level;
    }
    cout << "Level released\n" << endl;
    return;
}

bool Game::isGameFinished() {
    cout << "Checking if game is finished...\n" << endl;
    return this->quitGame;
}

bool Game::isLevelFinished() {
    cout << "Checking end of level...\n" << endl;
    return this->quitLevel;
}

void Game::init() {
    cout << "initializing..." << endl;

    initGUI();

    FRAME_MILISECOND = 1000 / SCREEN_FPS;
    this->quitGame = false;
    this->quitLevel = false;

    cout << "Game started\n" << endl;
    return;
}

void Game::shutdown() {
    cout << "Shutting Down..." << endl;
    closeGUI();
    cout << "Finalized" << endl;
    return;
}

void Game::loop() {
    do {
        loadLevel();

        //Level Loop
        do {
            updateTimeStep();
            recieveNetworkData();
            handleEvents();
            runAI();
            runPhysics();
            update();
            sendNetworkData();
            draw();
        }
        while(isLevelFinished() == false);
        releaseLevel();
    }
    while(isGameFinished() == false);
    return;
}

