#include "CGAME.h"

CGAME::CGAME(CENDSCREEN* endScreen) {
	player = CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);

	for (int i = 0; i < OBJECT_LIMIT; i++) {
		carsVect.push_back(new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y));
		busesVect.push_back(new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y));
		rabbitsVect.push_back(new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y));
		catsVect.push_back(new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y));
	}

	tfLightCars = CTRAFFICLIGHT(20, 10);
	tfLightBuses = CTRAFFICLIGHT(15, 10);
	this->endScreen = endScreen;

	level = 1;
	isInProgress = true;
}

CGAME::~CGAME() {
	for (int i = 0; i < OBJECT_LIMIT; i++) {
		delete carsVect[i], carsVect[i] = nullptr;
		delete busesVect[i], busesVect[i] = nullptr;
		delete rabbitsVect[i], rabbitsVect[i] = nullptr;
		delete catsVect[i], catsVect[i] = nullptr;
	}

	endScreen = nullptr;
}

template<class Obj>
bool CGAME::isValidDistance(Obj*& obj1, Obj*& obj2) {
	return abs(obj1->getX() - obj2->getX()) >= OBJECT_GAP + obj1->getWidth();
}

void CGAME::updatePosPeople() {
	if (CCONSOLE::isPressed('W')) player.goUp();
	if (CCONSOLE::isPressed('S')) player.goDown();
	if (CCONSOLE::isPressed('A')) player.goLeft();
	if (CCONSOLE::isPressed('D')) player.goRight();
}

void CGAME::updatePosVehicle() {
	updatePosObject(carsVect);
	updatePosObject(busesVect);
}

void CGAME::updatePosAnimal() {
	updatePosObject(rabbitsVect);
	updatePosObject(catsVect);
}

template<class Obj>
void CGAME::updatePosObject(vector<Obj*>& objVect) {
	for (int i = 0; i < objVect.size(); i++) {
		if (objVect[i]->canMove()) {
			objVect[i]->move();
			if (player.isImpact(objVect[i])) player.setDead(true);
			continue;
		}

		for (int j = 0; j < objVect.size(); j++)
			if (i != j)
				if (objVect[j]->canMove()) {
					if (!isValidDistance(objVect[i], objVect[j])) {
						objVect[i]->setMove(false);
						break;
					}
				} else objVect[i]->setMove(true);
	}
}

void CGAME::runGameOver() {
	CCONSOLE::clearScreen();
	isInProgress = false;
	endScreen->runEndScreen(true);
}

void CGAME::renewObjects() {
	for (int i = 0; i < OBJECT_LIMIT; i++) {
		delete carsVect[i];
		carsVect[i] = new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y);

		delete busesVect[i];
		busesVect[i] = new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y);

		delete rabbitsVect[i];
		rabbitsVect[i] = new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y);

		delete catsVect[i];
		catsVect[i] = new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y);
	}

	player = CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);
}

void CGAME::initGameGraphics() {
	CCONSOLE::clearScreen();
	CCONSOLE::drawGraphics(FIELD_SPRITE, { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, FIELD_COLOR);
}

void CGAME::runGame() {
	while (isInProgress) {
		tfLightCars.updateLightStatus(carsVect, vehicles::CAR);
		tfLightBuses.updateLightStatus(busesVect, vehicles::BUS);
		
		if (!player.isDead()) {
			CCONSOLE::drawGraphics(HUMAN_SPRITE, { player.getX(), player.getY() }, HUMAN_COLOR);
			updatePosPeople();
		}

		updatePosVehicle();
		updatePosAnimal();

		if (player.isDead()) {
			runGameOver();
			return;
		}

		Sleep(300);
	}
}

void CGAME::resetGame() {
	renewObjects();
	level = 1;
	initGameGraphics();
	isInProgress = true;
}

void CGAME::terminateGame(thread& gameRunner) {
	CCONSOLE::clearScreen();
	isInProgress = false;
	gameRunner.join();
}

bool CGAME::isRunning() {
	return isInProgress;
}