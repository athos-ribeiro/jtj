#ifndef JACK_H
#define JACK_H

#include "gameobject.h"
#include "level.h"
#include <string>

class Jack : public GameObject {
    SDL_Surface *jack;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;

    bool dead;

	int lastMove;
	int lastButOneMove;
    int frame; //for animation

    SDL_Rect spriteClips[9];
    public:
		int	strength;
        int speed;
        int verticalSpeed;
        bool jumping;
        static const int ACCELERATION = 1;
        static const int JACK_WIDTH = 38;
        static const int JACK_HEIGHT = 57;

        Jack(std::string filename);
        ~Jack();

        bool isDead();
        void die();

        void setSpriteClips();
        void move(int xBegin, int xRange, int yBegin, int yRange);
        void pushMove(int v);
        void popMove(int v);
        void jump(Level* level);
        int getXPosition();
        int getYPosition();
        void pushBox();
};

#endif

