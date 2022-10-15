#pragma once
#include "CGAME.h"

CGAME::CGAME() {
	player = CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);
	car = CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y);
}

void CGAME::initGame() {
	system("cls");
	CCONSOLE::drawGraphics("assets/gameInterfaces/playfield.txt", { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, 112);
}

void CGAME::runGame() {
	while (1) {
		if (!player.isDead()) {
			CCONSOLE::drawGraphics("assets/objects/human.txt", player.getCoord(), 112);
			updatePosPeople();
		}

		updatePosObject(&car);
		Sleep(300);
	}
}

void CGAME::updatePosPeople() {
	if (CCONSOLE::isPressed('W')) player.goUp();
	if (CCONSOLE::isPressed('S')) player.goDown();
	if (CCONSOLE::isPressed('A')) player.goLeft();
	if (CCONSOLE::isPressed('D')) player.goRight();
}

template<class Obj>
void CGAME::updatePosObject(Obj* obj) {
	obj->move();
}