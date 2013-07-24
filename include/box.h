#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include <string>

class Box : public GameObject {
    SDL_Surface *box;
    void drawSelf(SDL_Surface *surface);
    int speed;
    bool lyingDown;
    static const int ACCELERATION = 1;
    public:
		static const int WIDTH = 38;
        int x_position;
        int y_position;
        bool used;

        Box(std::string filename);
        ~Box();

        int getPositionX();
        int getPositionY();
        int getSpeed();
        void setPosition(int x, int y);
        void accelerate();
        void fall(int grid[12]);
};

#endif
