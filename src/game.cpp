#include <iostream>
#include "game.h"
#include "jack.h"
#include "level.h"
#include "box.h"

using namespace std;

void Game::initGUI() {
    cout << "initializing GUI..." << endl;

    //Initializing SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Setting Window title
    SDL_WM_SetCaption("Jack, The Janitor", NULL);
    //Set Window icon
    SDL_WM_SetIcon(IMG_Load("resources/Logo_WareHouse_64x64.png"), NULL);
    //Setting Screen
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);

    cout << "GUI started\n" << endl;
}

void Game::closeGUI() {
    cout << "closing GUI..." << endl;

    SDL_Delay(5000);
    SDL_Quit();

    cout << "GUI closed\n" << endl;
}

void Game::loadCommonResources() {
    cout << "loading common resources..." << endl;
    cout << "common resources started\n" << endl;
}

void Game::releaseCommonResources() {
    cout << "releasing common resources..." << endl;
    cout << "common resources released\n" << endl;
}

void Game::loadProfile() {
    cout << "loading profile..." << endl;
    cout << "Profile loaded\n" << endl;
}

void Game::saveProfile() {
    cout << "saving profile..." << endl;
    cout << "Profile saved\n" << endl;
}

void Game::updateTimeStep() {
    cout << "Updating time step..." << endl;
    cout << "time step updated.\n" << endl;
}

void Game::handleEvents() {
    cout << "handling events..." << endl;
    cout << "events handled.\n" << endl;
}

void Game::runAI() {
    cout << "Running AI..." << endl;
    cout << "AI done.\n" << endl;
}

void Game::runPhysics() {
    cout << "Running physics..." << endl;
    cout << "Physics done.\n" << endl;
}

void Game::update() {
    cout << "Updating entities..." << endl;
    cout << "Entities updated.\n" << endl;
}

void Game::recieveNetworkData() {
    cout << "Sending and recieving packages..." << endl;
    cout << "Packages handled.\n" << endl;
}

void Game::sendNetworkData() {
    cout << "Sending and recieving packages..." << endl;
    cout << "Packages handled.\n" << endl;
}


void Game::draw() {
    cout << "Drawing..." << endl;

    Level *level = new Level();
    level->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0xFF, 0xFF));

    this->jack = new Jack(38 + Level::LEVEL_X_OFFSET, Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Jack::JACK_HEIGHT);
    this->jack->draw(this->screen, SDL_MapRGB(this->screen->format, 0x00, 0x00, 0xAF));

    Box *box1 = new Box(38, 38, Level::LEVEL_X_OFFSET, 250);
    box1->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0xFF));

    Box *box2 = new Box(38, 38, Level::LEVEL_X_OFFSET + 10*38, 180);
    box2->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0xFF));

    Box *box3 = new Box(38, 38, Level::LEVEL_X_OFFSET+ 4*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38);
    box3->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0xFF));

    Box *box4 = new Box(38, 38, Level::LEVEL_X_OFFSET+ 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38);
    box4->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0xA0));

    Box *box5 = new Box(38, 38, Level::LEVEL_X_OFFSET+ 5*38, Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 38*2);
    box5->draw(this->screen, SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0x6F));

    SDL_Flip(this->screen);

    cout << "Drawing done.\n" << endl;
}

void Game::loadLevel() {
    cout << "Loading level..." << endl;
    cout << "Level loaded\n" << endl;
}

void Game::releaseLevel() {
    cout << "Releasing Level..." << endl;
    cout << "Level released\n" << endl;
}

bool Game::isGameFinished() {
    cout << "Checking if game is finished...\n" << endl;
    return true;
}

bool Game::isLevelFinished() {
    cout << "Checking end of level...\n" << endl;
    return true;
}

void Game::init() {
    cout << "initializing..." << endl;
    initGUI();
    cout << "Game started\n" << endl;
}

void Game::shutdown() {
    cout << "Shutting Down..." << endl;
    closeGUI();
    cout << "Finalized" << endl;
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
}

