#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include "level.h"
#include <string>

class Box : public GameObject {
    SDL_Surface *box;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;
    int speed;
    bool lyingDown;
    static const int ACCELERATION = 1;
    public:
        Box(std::string filename);
        ~Box();

        void setPosition(int x, int y);
        void accelerate();
        void fall(Level* level);
};

#endif
