#ifndef JACK_H
#define JACK_H

#include "gameobject.h"
#include <string>

class Jack : public GameObject {
    SDL_Surface *jack;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;
    public:
        static const int JACK_WIDTH = 38;
        static const int JACK_HEIGHT = 57;

        Jack(std::string filename);
        ~Jack();

        void move();
        void jump();
};

#endif

