#include "optionsscreen.h"
#include "sdlutil.h"

using namespace std;

OptionsScreen::OptionsScreen(string filename)
{
	this->optionsScreen = SDLUtil::loadImage(filename.c_str());
	this-> helpMessage = SDLUtil::loadImage("resources/helpTextImage.png");
}

OptionsScreen::~OptionsScreen()
{
	if (this->optionsScreen != NULL)
	{
		SDL_FreeSurface(this->optionsScreen);
	}
	if (this->helpMessage != NULL)
	{
		SDL_FreeSurface(this->helpMessage);
	}
}

void OptionsScreen::drawSelf(SDL_Surface *surface)
{
	SDLUtil::applySurface(0, 0, this->optionsScreen, surface);
	SDLUtil::applySurface(20, 100, this->helpMessage, surface);
	return ;
}
