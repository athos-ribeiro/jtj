#include "enemy.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

Enemy::Enemy(string filename) {
    this->enemy = SDLUtil::loadImage(filename);
    this->x_position = ENEMY_WIDTH + Level::LEVEL_X_OFFSET + 76;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Enemy::ENEMY_HEIGHT - 38*8 - 1;
}

Enemy::~Enemy() {
    if(enemy != NULL) {
        SDL_FreeSurface(enemy);
    }
}

void Enemy::drawSelf(SDL_Surface *surface) {
    SDLUtil::applySurface(this->x_position, this->y_position, this->enemy, surface);
    return;
}

void Enemy::move() {
    return;
}

void Enemy::throwBox(Box* box, vector<Box*> boxes) {
    box->setPosition(x_position, y_position - 57);
    boxes.push_back(box);
    return;
}
