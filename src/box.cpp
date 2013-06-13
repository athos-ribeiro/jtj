#include "box.h"

using namespace std;

Box::Box(int w, int h, int x, int y) {
    this->box.w = w;
    this->box.h = h;
    this->box.x = x;
    this->box.y = y;
}

Box::~Box() {
}

void Box::draw(SDL_Surface *surface, Uint32 color) {
    SDL_FillRect(surface, &this->box, color);
}

void Box::accelerate() {
}
