#include "enemy.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

Enemy::Enemy(string filename) {
    this->enemy = SDLUtil::loadImage(filename);
    this->x_position = Level::LEVEL_X_OFFSET;
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
    if(x_position >= 506) {
        x_position -= 456-38;
    }
    else {
        x_position += 1;
    }
    return;
}

void Enemy::throwBox(vector<Box*> boxes) {
    for(unsigned int i = 0; i < boxes.size(); i++) {
        if(boxes.at(i)->used == false) {
            boxes.at(i)->used = true;
            boxes.at(i)->setPosition(x_position, y_position - Enemy::ENEMY_HEIGHT);
            return;
        }
    }
    return;
}
