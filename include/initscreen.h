#ifndef INITSCREEN_H
#define INITSCREEN_H

#include "gameobject.h"
#include <string>

class InitScreen : public GameObject {
    SDL_Surface *initScreen;
    void drawSelf(SDL_Surface *surface);
    public:
        static const int LEVEL_WIDTH = 854;
        static const int LEVEL_HEIGHT = 480;

        InitScreen(std::string filename);
        ~InitScreen();

};

#endif
