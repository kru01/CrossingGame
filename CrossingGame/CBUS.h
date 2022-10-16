#pragma once
#include "CVEHICLE.h"
#include "CCONSTANT.h"

const int BUS_WIDTH = 18, BUS_HEIGHT = 4;
const int BUS_COLOR = colors::BLACK; 
const POINT BUS_SPAWN_COORD = { fieldConstraints::BOUND_RIGHT - BUS_WIDTH, fieldConstraints::BOUND_BOTTOM - 2*VER_SPEED - BUS_HEIGHT }; 

class CBUS : public CVEHICLE {
public:
	CBUS() = default;
	CBUS(int x, int y); 

	void move(); 
};