#pragma once
#include "CCONSOLE.h"
#include "CCONSTANT.h"

class CVEHICLE {
protected:
	int x, y, width, height;
	bool isMoving, isInRedLight;

public:
	CVEHICLE() = default;
	CVEHICLE(int x, int y);

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

	void setRedLight(bool flag);
	bool isRedLight();
};