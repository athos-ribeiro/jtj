#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "box.h"
#include <string>
#include <vector>

class Enemy : public GameObject {
    SDL_Surface *enemy;
    void drawSelf(SDL_Surface *surface);

    int frame;
    SDL_Rect spriteClips[8];
    public:
        void setSpriteClips();
        int x_position;
        int y_position;
        int movesLeft;
        int moveDirection;
        static const int ENEMY_WIDTH = 38;
        static const int ENEMY_HEIGHT = 57;

        Enemy(std::string filename);
        ~Enemy();

        void move();
        void throwBox(vector<Box*> boxes);
};

#endif

