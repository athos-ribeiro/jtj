#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include <string>

class Box : public GameObject {
    SDL_Surface *box;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;
    int speed;
    int acceleration;
    public:
        Box(std::string filename);
        ~Box();

        void setPosition(int x, int y);
        void accelerate();
};

#endif
