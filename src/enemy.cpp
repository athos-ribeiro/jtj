#include "enemy.h"
#include "level.h"
#include "sdlutil.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Enemy::Enemy(string filename) {
    this->enemy = SDLUtil::loadImage(filename);
    this->x_position = Level::LEVEL_X_OFFSET + 38;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Enemy::ENEMY_HEIGHT - 38*8 - 1;
    movesLeft = 0;
    moveDirection = 0;
    srand((unsigned)time(0));
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
    if(movesLeft > 0 && moveDirection%2 == 0) {
        x_position+= 2;
        movesLeft-=2;
    }
    else if(movesLeft > 0 && moveDirection%2 == 1) {
        x_position-=2;
        movesLeft-=2;
    }
    if(x_position <= Level::LEVEL_X_OFFSET) {
        x_position+= 2;
        movesLeft = 36;
        moveDirection = 2;
    }
    if(x_position >= Level::LEVEL_X_OFFSET + Level::LEVEL_WIDTH - 38) {
        x_position-=2;
        movesLeft = 36;
        moveDirection = 1;
    }


    if(movesLeft <= 0) {
        //delay
        if(moveDirection > 0) {
            moveDirection--;
            return;
        }

        else {
            //gen  movesLeft and moveDirection
            movesLeft = (rand()%6)*38;
            moveDirection = (rand()%120);
            }
    }
    return;
}

void Enemy::throwBox(vector<Box*> boxes) {
    if((x_position-Level::LEVEL_X_OFFSET)%38 == 0) {
    if(movesLeft == 0 && moveDirection == 30) {
        for(unsigned int i = 0; i < boxes.size(); i++) {
            if(boxes.at(i)->used == false) {
                boxes.at(i)->used = true;
                boxes.at(i)->setPosition(x_position, y_position - Enemy::ENEMY_HEIGHT);
                return;
            }
        }
    }
    }
    return;
}
