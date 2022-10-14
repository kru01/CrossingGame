#pragma once
#include "CCONSOLE.h"
#include "CCONSTANT.h"

class CPEOPLE {
	short X, Y;
	int width, height;
	bool isAlive;

public:
	CPEOPLE() = default;
	CPEOPLE(short x, short y);

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	bool isDead();
	COORD getCoord();
	int getWidth();
};