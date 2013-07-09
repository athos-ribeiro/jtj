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

void Jack::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(this->x_position, this->y_position, this->jack, surface);
    return;
}

void Jack::move() {
    x_position += speed;
    return;
}

void Jack::jump() {
    int initialPosition = y_position;
    y_position += verticalSpeed;
    verticalSpeed++;
    return;
}
