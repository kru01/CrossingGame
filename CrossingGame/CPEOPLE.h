#pragma once
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CVEHICLE.h"

const int HUMAN_WIDTH = 3, HUMAN_HEIGHT = 3;
const int HUMAN_COLOR = colors::BLACK;
const POINT HUMAN_SPAWN_COORD = { (fieldConstraints::F_RIGHT + fieldConstraints::F_LEFT) / 2 - HUMAN_WIDTH, fieldConstraints::F_BOTTOM - HUMAN_HEIGHT };

class CPEOPLE {
	int x, y;
	bool isAlive;

public:
	CPEOPLE() = default;
	CPEOPLE(int x, int y);

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	bool isImpact(CVEHICLE* obj);

	void setDead(bool confirm);
	bool isDead();
	
	int getX();
	int getY();
};