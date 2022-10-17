#pragma once
#include "CVEHICLE.h"
#include "CCONSTANT.h"

const string CAR_SPRITE = "assets/objects/car.txt";
const int CAR_WIDTH = 14, CAR_HEIGHT = 4;
const int CAR_COLOR = colors::BLACK;
const POINT CAR_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, fieldConstraints::BOUND_BOTTOM - CAR_HEIGHT };

class CCAR : public CVEHICLE {
public:
	CCAR() = default;
	CCAR(int x, int y);

	void move();
};