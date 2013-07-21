#include "box.h"
#include "sdlutil.h"

using namespace std;

Box::Box(string filename) {
    this->box = SDLUtil::loadImage(filename);
    speed = 0;
}

Box::~Box() {
    if(box != NULL) {
        SDL_FreeSurface(box);
    }
}

void Box::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(this->x_position, this->y_position, this->box, surface);
}

void Box::setPosition(int x, int y) {
    this->x_position = x;
    this->y_position = y;
}

void Box::accelerate() {
}

void Box::fall(Level* level) {
    speed += ACCELERATION;
    y_position += speed;
    if(y_position >= Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38) {
        speed = 0;
        y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - 38;
        return;
    }
}

