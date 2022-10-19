#pragma once
#include "CCONSTANT.h"
#include "CVEHICLE.h"

const string RABBIT_SPRITE = "assets/objects/rabbit.txt";
const int RABBIT_WIDTH = 9, RABBIT_HEIGHT = 3;
const int RABBIT_COLOR = colors::BLACK;

const POINT RABBIT_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, fieldConstraints::BOUND_BOTTOM - VER_SPEED * 3 - RABBIT_HEIGHT };

class CRABBIT : public CVEHICLE {
public:
	CRABBIT() = default;
	CRABBIT(int x, int y);

	void move();
};