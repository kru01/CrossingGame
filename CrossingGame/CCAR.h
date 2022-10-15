#pragma once
#include "CVEHICLE.h"
#include "CCONSTANT.h"

const int CAR_WIDTH = 13, CAR_HEIGHT = 3;
const POINT CAR_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, fieldConstraints::BOUND_BOTTOM - CAR_HEIGHT };

class CCAR : public CVEHICLE {
public:
	CCAR() = default;
	CCAR(int x, int y) : CVEHICLE(x, y) {};

	void move();
};