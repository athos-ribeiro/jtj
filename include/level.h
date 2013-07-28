#ifndef LEVEL_H
#define LEVEL_H

#include "gameobject.h"
#include "box.h"
#include "enemy.h"
#include <string>
#include <vector>

class Level : public GameObject {
    SDL_Surface *level;
    void drawSelf(SDL_Surface *surface);
    //this stack shall handle the colision logic.
    public:
        vector<Enemy*> enemies;
		vector<Box*> boxes;
		vector<Box*> grid[12];

        static const int LEVEL_WIDTH = 456;
        static const int LEVEL_HEIGHT = 456;
        static const int LEVEL_X_OFFSET = 50;
        static const int LEVEL_Y_OFFSET = 10;

        Level(std::string filename);
        ~Level();

		vector<Box*> getBoxes();

};

#endif
