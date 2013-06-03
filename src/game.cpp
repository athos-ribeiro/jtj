#include <iostream>
#include "game.h"

using namespace std;

void Game::initGUI() {
    cout << "initializing GUI..." << endl;
    cout << "GUI started\n" << endl;
}

void Game::closeGUI() {
    cout << "closing GUI..." << endl;
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
    cout << "Game started\n" << endl;
}

void Game::shutdown() {
    cout << "Shutting Down..." << endl;
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

