#pragma once
#include "CVEHICLE.h"
#include "CCONSTANT.h"
#include "CTRAFFICLIGHT.h"

const string CAR_SPRITE = "assets/objects/car.txt";
const int CAR_WIDTH = 13, CAR_HEIGHT = 4;
const int CAR_COLOR = colors::RED;
const POINT CAR_SPAWN_COORD = { fieldConstraints::BOUND_LEFT, LANE_YCOORD[3] - CAR_HEIGHT};

class CCAR : public CVEHICLE {
public:
	CCAR() = default;
	CCAR(int x, int y);

	void move();
	void makeSound();
};