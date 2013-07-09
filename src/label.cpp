#include "label.h"
#include "sdlutil.h"
#include "level.h"

Label::Label(std::string filename, int xPosition, int yPosition) {
	this->label = SDLUtil::loadImage(filename);
	this->xPosition = LABEL_WIDTH + Level::LEVEL_X_OFFSET + xPosition;
	this->yPosition = LABEL_HEIGHT + Level::LEVE_Y_OFFSET + yPosition;
}

Label::~Label() {
	if (label != NULL) {
		SDL_FreeSurface(label);
	}
}

void
Label::drawSelf(SDL_Surface * surface) {
	SDLUtil::applySurface(this->xPosition, this->yPosition, this->label, surface);
}

bool
Label::wasClicked() {
	
}