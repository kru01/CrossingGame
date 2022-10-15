#pragma once
#include "CGAME.h"

CGAME::CGAME() {
	player = CPEOPLE((fieldConstraints::F_RIGHT + fieldConstraints::F_LEFT) / 2 - HUMAN_WIDTH, fieldConstraints::F_BOTTOM - HUMAN_HEIGHT);
}

void CGAME::initGame() {
	system("cls");
	CCONSOLE::drawGraphics("assets/gameInterfaces/playfield.txt", { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, 0);
}

void CGAME::runGame() {
	while (1) {
		if (!player.isDead()) {
			CCONSOLE::drawGraphics("assets/objects/human.txt", player.getCoord(), 0);
			updatePosOfPeople();
		}

		Sleep(300);
	}
}

void CGAME::updatePosOfPeople() {
	if (CCONSOLE::isPressed('W')) player.goUp();
	if (CCONSOLE::isPressed('S')) player.goDown();
	if (CCONSOLE::isPressed('A')) player.goLeft();
	if (CCONSOLE::isPressed('D')) player.goRight();
}