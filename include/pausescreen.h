#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "gameobject.h"
#include <string>

class PauseScreen : public GameObject {
    SDL_Surface *pauseScreen;
    void drawSelf(SDL_Surface *surface);
    public:
        static const int LEVEL_WIDTH = 854;
        static const int LEVEL_HEIGHT = 480;

        PauseScreen(std::string filename);
        ~PauseScreen();

};

#endif