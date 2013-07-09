#ifndef LABEL_H
#define LABEL_H

#include "gameobject.h"
#include <string>

class Label : public GameObject {
	SDL_Surface *label;
	void drawSelf(SDL_Surface * surface);
	int xPosition;
	int yPosition;
	public:
		static const int LABEL_WIDTH = 300;
		static const int LABEL_HEIGHT = 100;

		Label(std::string filename, int xPosition, int yPosition);
		~Label();
};

#endif