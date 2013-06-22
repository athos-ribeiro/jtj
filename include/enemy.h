#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include <string>

class Enemy : public GameObject {
    SDL_Surface *enemy;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;
    public:
        static const int ENEMY_WIDTH = 38;
        static const int ENEMY_HEIGHT = 57;

        Enemy(std::string filename);

        void move();
        void throwBox();
};

#endif

