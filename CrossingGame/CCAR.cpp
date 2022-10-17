#pragma once
#include "CCAR.h"

CCAR::CCAR(int x, int y) : CVEHICLE(x, y) {
	this->width = CAR_WIDTH;
	this->height = CAR_HEIGHT;
}

void CCAR::move() {
	if (isInRedLight) {
		CCONSOLE::drawGraphics(CAR_SPRITE, { x, y }, CAR_COLOR);
		return;
	}

	x += fieldConstraints::HOR_SPEED;

	if (x >= fieldConstraints::BOUND_RIGHT - CAR_WIDTH) {
		CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x + CAR_WIDTH, y + CAR_HEIGHT });
		isMoving = false;
		x = CAR_SPAWN_COORD.x;
		return;
	}

	CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x, y + CAR_HEIGHT });
	CCONSOLE::drawGraphics(CAR_SPRITE, { x, y }, CAR_COLOR);
}