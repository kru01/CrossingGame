#pragma once
#include "CCONSOLE.h"

class CANIMAL {
protected:
	int x, y, width, height;
	bool isMoving;

public:
	CANIMAL() = default;
	CANIMAL(int x, int y);

	virtual void move() = 0;
	
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setMove(bool confirm);
	bool canMove();
};