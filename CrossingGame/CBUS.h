#pragma once
#include "CVEHICLE.h"
#include "CCONSTANT.h"
#include "CTRAFFICLIGHT.h"

const string BUS_SPRITE = "assets/objects/bus.txt";
const int BUS_WIDTH = 17, BUS_HEIGHT = 4;
const int BUS_COLOR = colors::AQUA;
const POINT BUS_SPAWN_COORD = { fieldConstraints::BOUND_RIGHT - BUS_WIDTH, fieldConstraints::BOUND_BOTTOM - 2 * fieldConstraints::VER_SPEED - BUS_HEIGHT };

class CBUS : public CVEHICLE {
public:
	CBUS() = default;
	CBUS(int x, int y);

	void move();
};