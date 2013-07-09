#include "jack.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

Jack::Jack(string filename) {
    this->jack = SDLUtil::loadImage(filename);
    this->x_position = JACK_WIDTH + Level::LEVEL_X_OFFSET;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Jack::JACK_HEIGHT;
    this->speed = 0;
}

Jack::~Jack() {
    if(jack != NULL) {
        SDL_FreeSurface(jack);
    }
}

int setLimit(int value, int limit1, int limit2) {
    if(value<limit1)
        return limit1;
    if(value>=limit2)
        return (limit2-1);
    return value;
}

void Jack::drawSelf(SDL_Surface *surface) {
    this->x_position = setLimit(x_position, Level::LEVEL_X_OFFSET,Level::LEVEL_WIDTH);
    this->y_position = setLimit(y_position, Level::LEVEL_Y_OFFSET,Level::LEVEL_HEIGHT);
    SDLUtil::applySurface(this->x_position, this->y_position, this->jack, surface);
    return;
}

void Jack::move() {
    x_position += speed;
    return;
}

void Jack::jump() {
    return;
}
