#ifndef BOX_H
#define BOX_H

#include <SDL/SDL.h>

class Box {
    SDL_Rect box;
    int speed;
    int acceleration;
    public:
        Box(int w, int h, int x, int y);
        ~Box();

        SDL_Rect getBox();

        void draw(SDL_Surface *surface, Uint32 color);
        void accelerate();
};

#endif
