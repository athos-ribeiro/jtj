#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "gameobject.h"
#include <string>

class OptionsScreen : public GameObject
{
    SDL_Surface *helpMessage;
	SDL_Surface *optionsScreen;
	void drawSelf(SDL_Surface *surface);
public:
	static const int SCREEN_WIDTH = 854;
	static const int SCREEN_HEIGHT = 480;
	
	OptionsScreen(std::string filename);
	~OptionsScreen();

	/* data */
};
#endif
