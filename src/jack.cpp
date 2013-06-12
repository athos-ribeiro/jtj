#include "jack.h"

using namespace std;

Jack::Jack(int x, int y) {
    this->jack.w = JACK_WIDTH;
    this->jack.h = JACK_HEIGHT;
    this->jack.x = x;
    this->jack.y = y;
}

Jack::~Jack() {
}

SDL_Rect Jack::getJack() {
    return this->jack;
}

void Jack::draw(SDL_Surface *surface, Uint32 color) {
    SDL_FillRect(surface, &this->jack, color);
}

void Jack::move() {
}

void Jack::jump() {
}
