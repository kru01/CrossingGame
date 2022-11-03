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
	virtual void makeSound() = 0;
	
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getWidth();
	int getHeight();

	void setMove(bool flag);
	bool canMove();
};