#include "box.h"
#include "sdlutil.h"

using namespace std;

Box::Box(string filename) {
    this->box = SDLUtil::loadImage(filename);
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

