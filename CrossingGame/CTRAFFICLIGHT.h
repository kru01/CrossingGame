#pragma once
#include <vector>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CCAR.h"
#include "CBUS.h"

const string TFLIGHT_SPRITE = "assets/objects/trafficLight.txt";
const int TFLIGHT_WIDTH = 2, TFLIGHT_HEIGHT = 2;
const POINT TFLIGHT_CAR_LANE_COORD = { fieldConstraints::F_RIGHT - TFLIGHT_WIDTH, fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED + TFLIGHT_HEIGHT };
const POINT TFLIGHT_BUS_LANE_COORD = { fieldConstraints::F_LEFT, fieldConstraints::BOUND_BOTTOM - 3 * fieldConstraints::VER_SPEED + TFLIGHT_HEIGHT };

class CTRAFFICLIGHT {
	bool isRed;
	int greenTime, redTime, timeElapsed;

	void updateSprite(int& lane);

public:
	CTRAFFICLIGHT() = default;
	CTRAFFICLIGHT(int greenTime, int redTime);
	
	template<class Obj>
	void updateLightStatus(vector<Obj*>& objVect, int lane);
};