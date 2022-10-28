#pragma once
#include <vector>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CCAR.h"
#include "CBUS.h"

const string TFLIGHT_SPRITE = "assets/objects/trafficLight.txt";
const int TFLIGHT_WIDTH = 2, TFLIGHT_HEIGHT = 2;
const POINT TFLIGHT_CAR_LANE_COORD = { fieldConstraints::F_RIGHT - TFLIGHT_WIDTH, LANE_YCOORD[2] + TFLIGHT_HEIGHT};
const POINT TFLIGHT_BUS_LANE_COORD = { fieldConstraints::F_LEFT, LANE_YCOORD[0] + TFLIGHT_HEIGHT};

class CTRAFFICLIGHT {
	int x, y;
	bool isRed;
	int greenTime, redTime, timeElapsed;

	void updateSprite(int& lane);

public:
	CTRAFFICLIGHT() = default;
	CTRAFFICLIGHT(int vehicle);
	
	void setY(int y);

	static int calcTFLightYCoord(int lane);
	void eraseTFLightAndFixBoard(int vehicle);

	template<class Obj>
	void updateLightStatus(vector<Obj*>& objVect, int lane);
};