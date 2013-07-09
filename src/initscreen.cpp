#include "initscreen.h"
#include "sdlutil.h"

using namespace std;

InitScreen::InitScreen(string filename) {
    this->initScreen = SDLUtil::loadImage(filename);
}

InitScreen::~InitScreen() {
    if(initScreen != NULL) {
        SDL_FreeSurface(initScreen);
    }
}

//draws the level on the specified surface
void InitScreen::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(0, 0, this->initScreen, surface);
    return;
}
