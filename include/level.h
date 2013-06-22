#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"
#include <string>

class Level : public GameObject {
    SDL_Surface *level;
    void drawSelf(SDL_Surface *surface);
    public:
        static const int LEVEL_WIDTH = 456;
        static const int LEVEL_HEIGHT = 456;
        static const int LEVEL_X_OFFSET = 50;
        static const int LEVEL_Y_OFFSET = 10;

        Level(std::string filename);

};

#endif
