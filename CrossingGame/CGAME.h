#pragma once
#include <vector>
#include <thread>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CPEOPLE.h"
#include "CCAR.h"
#include "CBUS.h"
#include "CRABBIT.h"
#include "CCAT.h"
#include "CTRAFFICLIGHT.h"
#include "CENDSCREEN.h"

const string FIELD_SPRITE = "assets/gameInterfaces/playfield.txt";
const int FIELD_COLOR = colors::BLACK;
const int OBJECT_LIMIT = 5, OBJECT_GAP = 20;

class CGAME {
	CPEOPLE* player;
	vector<CPEOPLE*> humansVect;
	vector<CCAR*> carsVect;
	vector<CBUS*> busesVect;
	vector<CRABBIT*> rabbitsVect;
	vector<CCAT*> catsVect;

	CTRAFFICLIGHT tfLightCars;
	CTRAFFICLIGHT tfLightBuses;
	CENDSCREEN* endScreen;

	int level;
	bool isInProgress;

	template<class Obj>
	bool isValidDistance(Obj*& obj1, Obj*& obj2);

	void updatePosPeople();
	void updatePosVehicle();
	void updatePosAnimal();
	template<class Obj>
	void updatePosObject(vector<Obj*>& objVect);

	bool checkImpactPeopleAndDrawEffect();
	void impactPeopleEffect(CPEOPLE*& victim, int effectTime);

	bool advanceLevel();
	void runGameOver();
	void runGameWon();
	void renewObjects();

public:
	CGAME(CENDSCREEN* endScreen);
	~CGAME();

	static void initGameGraphics();
	void runGame();
	void resetGame();
	void terminateGame(thread& gameRunner);

	bool isRunning();
};