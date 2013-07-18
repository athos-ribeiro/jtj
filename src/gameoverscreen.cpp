#include "gameoverscreen.h"
#include "sdlutil.h"

using namespace std;

GameOverScreen::GameOverScreen(string filename) {
    this->gameOverScreen = SDLUtil::loadImage(filename);
}

GameOverScreen::~GameOverScreen() {
    if(gameOverScreen != NULL) {
        SDL_FreeSurface(gameOverScreen);
    }
}

//draws the level on the specified surface
void GameOverScreen::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(0, 0, this->gameOverScreen, surface);
    return;
}
