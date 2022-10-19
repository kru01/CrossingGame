#pragma once
#include "CCONSTANT.h"
#include "CANIMAL.h"

const string RABBIT_SPRITE = "assets/objects/rabbit.txt";
const int RABBIT_WIDTH = 8, RABBIT_HEIGHT = 3;
const int RABBIT_COLOR = colors::BLACK;

const POINT RABBIT_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED * 3 - RABBIT_HEIGHT };

class CRABBIT : public CANIMAL {
public:
	CRABBIT() = default;
	CRABBIT(int x, int y);

	void move();
};