#include "level.h"
#include "sdlutil.h"

using namespace std;

Level::Level(string filename) {
    this->level = SDLUtil::loadImage(filename);
}

//draws the level on the specified surface
void Level::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(Level::LEVEL_X_OFFSET, Level::LEVEL_Y_OFFSET, this->level, surface);
    return;
}
