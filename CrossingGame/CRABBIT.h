#pragma once
#include "CCONSTANT.h"
#include "CANIMAL.h"

const string RABBIT_SPRITE = "assets/objects/rabbit.txt";
const int RABBIT_WIDTH = 8, RABBIT_HEIGHT = 3;
const int RABBIT_COLOR = colors::YELLOW;
const POINT RABBIT_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, LANE_YCOORD[0] - RABBIT_HEIGHT};

class CRABBIT : public CANIMAL {
public:
	CRABBIT() = default;
	CRABBIT(int x, int y);

	void move();
	void makeSound();
};