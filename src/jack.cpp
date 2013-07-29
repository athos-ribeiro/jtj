#include "jack.h"
#include "level.h"
#include "sdlutil.h"

using namespace std;

Jack::Jack(string filename) {
    this->jack = SDLUtil::loadImage(filename);
    this->x_position = JACK_WIDTH + Level::LEVEL_X_OFFSET;
    this->y_position = Level::LEVEL_HEIGHT + Level::LEVEL_Y_OFFSET - Jack::JACK_HEIGHT - 38;
    this->speed = 0;
    this->dead = false;
    verticalSpeed = 0;
    jumping = false;
	lastMove=0;
	lastButOneMove=0;
	strength = 0;
    frame = 0;
}

Jack::~Jack() {
    if(jack != NULL) {
        SDL_FreeSurface(jack);
    }
}

void
Jack::die()
{
    this->dead = true;
}

bool
Jack::isDead()
{
    return this->dead;
}

int setLimit(int value, int limit1, int range) {
    int limit2=limit1+range;
    if(value<limit1)
        return limit1;
    if(value>=limit2)
        return (limit2);
    return value;
}

void Jack::drawSelf(SDL_Surface *surface) {

    if(jumping == true) {
        if(speed >= 0) {
            frame = 7;
        }
        else {
            frame = 8;
        }
    }
    else if(speed > 0) {
        frame ++;
        if(frame > 3) {
            frame = 1;
        }
    }
    else if(speed < 0) {
        frame++;
        if(frame < 4) {
            frame = 4;
        }
        if(frame > 6) {
            frame = 4;
        }
    }
    else {
        frame = 0;
    }
    SDLUtil::applySurface(this->x_position, this->y_position, this->jack, surface, &spriteClips[frame]);
    return;
}

void Jack::move(int xBegin, int xRange, int yBegin, int yRange) {
    x_position += speed;
    this->x_position = setLimit(x_position, xBegin, xRange-JACK_WIDTH);
    this->y_position = setLimit(y_position, yBegin, yRange-JACK_HEIGHT - 38);
    return;
}

void Jack::jump(Level* level) {
    y_position += verticalSpeed;
    verticalSpeed += ACCELERATION;

    if(jumping == true) {
        if ((y_position >= (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38))) || (y_position >= (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position+37 - Level::LEVEL_X_OFFSET)/38].size()*38)))) {
        jumping = false;
        verticalSpeed = 1;
        }
    }

    //these next two if's handles boxes superior colision.
    if(y_position >= (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38))) {
        y_position = (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position - Level::LEVEL_X_OFFSET)/38].size()*38));
        verticalSpeed = 1;
        //verticalSpeed -= ACCELERATION;
    }
    else if(y_position >= (int)(Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position+37 - Level::LEVEL_X_OFFSET)/38].size()*38))) {
        y_position = Level::LEVEL_Y_OFFSET + Level::LEVEL_HEIGHT - 57 -38 - (level->grid[(x_position+37 - Level::LEVEL_X_OFFSET)/38].size()*38);
        verticalSpeed = 1;
        //verticalSpeed -= ACCELERATION;
    }
    //this avoids double jumping while falling from a box
    else {
        jumping = true;
    }
    //verticalSpeed++;
    return;
}

void Jack::pushMove(int v) {
		if(lastMove==0) {
			speed=v;
			lastMove=v;
		}
	else if (lastButOneMove==0) {
			speed=v;
			lastButOneMove=v;
		}
	return;
}

void Jack::popMove(int v) {
	if(lastButOneMove==v) {
		lastButOneMove=0;
		speed=lastMove;
	}
	else if(lastMove==v) {
		if(lastButOneMove!=0) {
			speed=lastButOneMove;
			lastMove=lastButOneMove;
			lastButOneMove=0;
		}
		else {
			lastMove=0;
			speed=0;
			/*
			int rest = x_position%Box::BOX_WIDTH;
			if(rest<10) {
				x_position -=rest;
			}
			else if(rest>(Box::BOX_WIDTH-10)) {
				x_position +=Box::BOX_WIDTH-rest-1;
			}
			*/

		}
	}
}
int Jack::getXPosition() {
	return this->x_position;
}
int Jack::getYPosition() {
	return this->y_position;
}

void Jack::pushBox() {
}

void Jack::setSpriteClips() {
    spriteClips[0].x = 0;
    spriteClips[0].y = JACK_HEIGHT;
    spriteClips[0].w = JACK_WIDTH;
    spriteClips[0].h = JACK_HEIGHT;

    spriteClips[1].x = JACK_WIDTH;
    spriteClips[1].y = JACK_HEIGHT;
    spriteClips[1].w = JACK_WIDTH;
    spriteClips[1].h = JACK_HEIGHT;

    spriteClips[2].x = JACK_WIDTH*2;
    spriteClips[2].y = JACK_HEIGHT;
    spriteClips[2].w = JACK_WIDTH;
    spriteClips[2].h = JACK_HEIGHT;

    spriteClips[3].x = JACK_WIDTH*3;
    spriteClips[3].y = JACK_HEIGHT;
    spriteClips[3].w = JACK_WIDTH;
    spriteClips[3].h = JACK_HEIGHT;

    spriteClips[4].x = JACK_WIDTH;
    spriteClips[4].y = 0;
    spriteClips[4].w = JACK_WIDTH;
    spriteClips[4].h = JACK_HEIGHT;

    spriteClips[5].x = JACK_WIDTH*2;
    spriteClips[5].y = 0;
    spriteClips[5].w = JACK_WIDTH;
    spriteClips[5].h = JACK_HEIGHT;

    spriteClips[6].x = JACK_WIDTH*3;
    spriteClips[6].y = 0;
    spriteClips[6].w = JACK_WIDTH;
    spriteClips[6].h = JACK_HEIGHT;

    spriteClips[7].x = JACK_WIDTH*4;
    spriteClips[7].y = JACK_HEIGHT;
    spriteClips[7].w = JACK_WIDTH;
    spriteClips[7].h = JACK_HEIGHT;

    spriteClips[8].x = JACK_WIDTH*4;
    spriteClips[8].y = 0;
    spriteClips[8].w = JACK_WIDTH;
    spriteClips[8].h = JACK_HEIGHT;
}
