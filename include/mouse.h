#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
	int x;
	int y;
	bool wasPressed;
	Mouse mouse;
	Mouse();

public:
	Mouse getMouse();
	void pressed(int x, int y);
	void released();
	~Mouse();
};

#endif