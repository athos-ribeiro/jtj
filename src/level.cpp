#include "level.h"

using namespace std;

Level::Level() {
    this->level.w = LEVEL_WIDTH;
    this->level.h = LEVEL_HEIGHT;
    this->level.x = LEVEL_X_OFFSET;
    this->level.y = LEVEL_Y_OFFSET;
}

Level::~Level() {
}

void Level::draw(SDL_Surface *surface, Uint32 color) {
    SDL_FillRect(surface, &this->level, color);
}
