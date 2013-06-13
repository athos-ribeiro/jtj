#ifndef JACK_H
#define JACK_H

#include <SDL/SDL.h>

class Jack {
    SDL_Rect jack;

    public:
        static const int JACK_WIDTH = 38;
        static const int JACK_HEIGHT = 57;
        Jack(int x, int y); //where x and y are the positions of Jack on the screen.
        ~Jack();

        SDL_Rect getJack();

        //the color will not be needed after the game art is complete and shall be removed.
        void draw(SDL_Surface *surface, Uint32 color);
        void move();
        void jump();
};

#endif

