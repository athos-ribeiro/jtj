#ifndef LEVEL_H
#define LEVEL_H

#include <SDL/SDL.h>

class Level {
    SDL_Rect level;
    public:
        static const int LEVEL_WIDTH = 456;
        static const int LEVEL_HEIGHT = 450;
        static const int LEVEL_X_OFFSET = 50;
        static const int LEVEL_Y_OFFSET = 10;


        Level();
        ~Level();

        void draw(SDL_Surface *surface, Uint32 color);
};

#endif
