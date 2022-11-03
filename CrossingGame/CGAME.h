#pragma once
#include <vector>
#include <set>
#include <thread>
#include <filesystem>
#include <algorithm>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CPEOPLE.h"
#include "CCAR.h"
#include "CBUS.h"
#include "CRABBIT.h"
#include "CCAT.h"
#include "CTRAFFICLIGHT.h"
#include "CMAINMENU.h"
#include "CENDSCREEN.h"

// FIELD_SPRITE and FIELD_COLOR are in CCONSTANT.h
const int OBJECT_ONSCREEN_LIMIT = 5, OBJECT_GAP = 20;
const int EFFECT_LOOP = 5, EFFECT_DURATION = 200;
const int RENDER_SPEED = 300; // lower is faster but laggier

const string SAVEFILE_PATH = "assets/savefiles/";
const string SAVEFILE_EXTENSION = ".bin";
const int SAVEFILE_LIMIT = 10, SAVEFILE_MAX_LENGTH = 10;

class CGAME {
	CPEOPLE* player;
	vector<CPEOPLE*> humansVect;
	vector<CCAR*> carsVect;
	vector<CBUS*> busesVect;
	vector<CRABBIT*> rabbitsVect;
	vector<CCAT*> catsVect;
	set<string> savesSet;

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
	void impactPeopleEffect(CPEOPLE*& victim);
	void playerWinEffect();
	void playerDeadEffect();

	void clearLane(int lane);
	void clearAllLane();
	void assignLaneRandomly();

	static void drawGameStatus(bool isRunning);
	static void drawLevelNum(int level);
	void drawHumansVect();
	void eraseTextBoxContent();

	bool advanceLevel();
	void runGameOver();
	void runGameWon();
	void renewObjects();

	void getSavefilePath(string& savefile);
	void listSavefile(bool isInGame);
	static void decapitalizeString(string& str);
	void standardizeFilename(string& filename);
	string promptSavefileName(bool isInGame);

	template<class Obj>
	void writeObjectToFile(ofstream& fout, const vector<Obj*>& objVect);
	template<class Obj>
	void writeTFLightToFile(ofstream& fout, Obj& tfLight);
	template<class Obj>
	void readObjectFromFile(ifstream& fin, vector<Obj*>& objVect);
	template<class Obj>
	void readTFLightFromFile(ifstream& fin, Obj& tfLight);

	void populateHumansVect();

public:
	CGAME(CENDSCREEN* endScreen);
	~CGAME();

	void initGameGraphics();

	void runGame();
	void resetGame();
	void terminateGame(thread& gameRunner);

	void resumeGame();
	void pauseGame();
	void saveGame();
	bool loadGame(bool isInGame);

	int getLevel();
	void setLevel(int level);

	bool isRunning();
	bool isPlayerDead();
};