#pragma once
#include "CCONSOLE.h"
#include "CCONSTANT.h"

class CVEHICLE {
protected:
	int x, y, width, height;
	bool isMoving;

public:
	CVEHICLE() = default;
	CVEHICLE(int x, int y);

	virtual void move() = 0;

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setMove(bool flag);
	bool canMove();
};