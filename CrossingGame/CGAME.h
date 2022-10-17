#pragma once
#include <vector>
#include "CCONSOLE.h"
#include "CPEOPLE.h"
#include "CCAR.h"
#include "CBUS.h"
#include "CCONSTANT.h"

const int FIELD_COLOR = colors::BLACK;
const int OBJECT_LIMIT = 5, OBJECT_GAP = 15;

class CGAME {
	CPEOPLE player;
	vector<CCAR*> carsVect;
	vector<CBUS*> busesVect; 

	int level;

	template<class Obj>
	bool isValidDistance(Obj*& obj1, Obj*& obj2);

	void updatePosPeople();
	void updatePosVehicle();
	template<class Obj>
	void updatePosObject(vector<Obj*>& objVect);

public:
	CGAME();

	static void initGame();
	void runGame();
};