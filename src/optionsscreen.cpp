#include "optionsscreen.h"
#include "sdlutil.h"

using namespace std;

OptionsScreen::OptionsScreen(string filename)
{
	this->optionsScreen = SDLUtil::loadImage(filename);
}

OptionsScreen::~OptionsScreen()
{
	if (optionsScreen != NULL)
	{
		SDL_FreeSurface(optionsScreen);
	}
}

void OptionsScreen::drawSelf(SDl_Surface *surface)
{
	SDLUtil::applySurface(0, 0, this->optionsScreen, surface);

	return ;
}
