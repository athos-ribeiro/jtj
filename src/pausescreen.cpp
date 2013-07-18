#include "pausescreen.h"
#include "sdlutil.h"

using namespace std;

PauseScreen::PauseScreen(string filename) {
    this->pauseScreen = SDLUtil::loadImage(filename);
}

PauseScreen::~PauseScreen() {
    if(pauseScreen != NULL) {
        SDL_FreeSurface(pauseScreen);
    }
}

//draws the level on the specified surface
void PauseScreen::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(0, 0, this->pauseScreen, surface);
    return;
}
