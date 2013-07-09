#include "mouse.h"


Mouse::Mouse() {
	this->x = 0;
	this->y = 0;
	this->wasPressed = false;
}

Mouse::~Mouse() {

}

void
Mouse::pressed(int x, int y) {
	this->x = x;
	this->y = y;
	this->wasPressed = true;
	
	return;
}

void
Mouse::released() {
	this->wasPressed = false;

	return;
}


Mouse
Mouse::getMouse() {
	if (!mouse) {
		mouse = new Mouse();
	}

	return mouse;
}