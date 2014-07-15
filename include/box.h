#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include <string>

class Box : public GameObject {
    SDL_Surface *box;
    void drawSelf(SDL_Surface *surface);
    float speed;
    static const int ACCELERATION = 1;
    static const int MAX_SPEED = 3;
    public:
		bool lyingDown;
		static const int BOX_WIDTH = 38;
		static const int BOX_HEIGHT = 38;
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
		void fall(vector<Box*>grid[12]);
};

#endif
