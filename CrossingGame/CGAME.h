#pragma once
#include <vector>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CPEOPLE.h"
#include "CCAR.h"
#include "CBUS.h"
#include "CRABBIT.h"
#include "CCAT.h"
#include "CTRAFFICLIGHT.h"

const string FIELD_SPRITE = "assets/gameInterfaces/playfield.txt";
const int FIELD_COLOR = colors::BLACK;
const int OBJECT_LIMIT = 5, OBJECT_GAP = 15;

class CGAME {
	CPEOPLE player;
	vector<CCAR*> carsVect;
	vector<CBUS*> busesVect;
	vector<CRABBIT*> rabbitsVect;
	vector<CCAT*> catsVect;

	CTRAFFICLIGHT tfLightCars;

	int level;

	template<class Obj>
	bool isValidDistance(Obj*& obj1, Obj*& obj2);

	void updatePosPeople();
	void updatePosVehicle();
	void updatePosAnimal();
	template<class Obj>
	void updatePosObject(vector<Obj*>& objVect);

public:
	CGAME();
	~CGAME();

	static void initGame();
	void runGame();
};