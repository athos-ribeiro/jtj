#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "gameobject.h"
#include <string>

class GameOverScreen : public GameObject {
    SDL_Surface *gameOverScreen;
    void drawSelf(SDL_Surface *surface);
    public:
        static const int LEVEL_WIDTH = 854;
        static const int LEVEL_HEIGHT = 480;

        GameOverScreen(std::string filename);
        ~GameOverScreen();

};

#endif