#pragma once
#include "CGAME.h"

CGAME::CGAME() {
	player = CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);
	
	for (int i = 0; i < OBJECT_LIMIT; i++) {
		carsVect.push_back(new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y));
	}

	level = 1;
}

void CGAME::initGame() {
	system("cls");
	CCONSOLE::drawGraphics("assets/gameInterfaces/playfield.txt", { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, FIELD_COLOR);
}

void CGAME::runGame() {
	srand(time(NULL));

	while (1) {
		if (!player.isDead()) {
			CCONSOLE::drawGraphics("assets/objects/human.txt", { player.getX(), player.getY() }, HUMAN_COLOR);
			updatePosPeople();
		}

		updatePosObject(carsVect);
		Sleep(300);
	}
}

template<class Obj>
bool CGAME::isValidDistance(Obj*& obj1, Obj*& obj2) {
	return abs(obj1->getX() - obj2->getX()) >= OBJECT_GAP;
}

void CGAME::updatePosPeople() {
	if (CCONSOLE::isPressed('W')) player.goUp();
	if (CCONSOLE::isPressed('S')) player.goDown();
	if (CCONSOLE::isPressed('A')) player.goLeft();
	if (CCONSOLE::isPressed('D')) player.goRight();
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