#include "label.h"
#include "sdlutil.h"
#include "level.h"

Label::Label(std::string filename, int xPosition, int yPosition) {
	this->label = SDLUtil::loadImage(filename);
	this->xPosition = xPosition;
	this->yPosition = yPosition;
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
Label::wasClicked(int xMouse, int yMouse) {
	if (xMouse > this->xPosition && xMouse < this->xPosition + LABEL_WIDTH && yMouse > this->yPosition && yMouse < this->yPosition + LABEL_HEIGHT) {
		return true;
	}

	return false;
}