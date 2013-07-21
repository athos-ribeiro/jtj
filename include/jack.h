#ifndef JACK_H
#define JACK_H

#include "gameobject.h"
#include <string>

class Jack : public GameObject {
    SDL_Surface *jack;
    void drawSelf(SDL_Surface *surface);
    int x_position;
    int y_position;

	int lastMove;
	int lastButOneMove;
    public:
        int speed;
        int verticalSpeed;
        bool jumping;
        static const int ACCELERATION = 1;
        static const int JACK_WIDTH = 38;
        static const int JACK_HEIGHT = 57;

        Jack(std::string filename);
        ~Jack();

        void move();
		void pushMove(int v);
		void popMove(int v);
        void jump();
};

#endif

