#pragma once
#include "CCAR.h"

void CCAR::move() {
	x += fieldConstraints::HOR_SPEED;

	if (x >= fieldConstraints::BOUND_RIGHT - CAR_WIDTH) {
		CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x + CAR_WIDTH, y + CAR_HEIGHT });
		x = CAR_SPAWN_COORD.x;
		return;
	}

	CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x, y + CAR_HEIGHT });
	CCONSOLE::drawGraphics("assets/objects/car.txt", { x, y }, 112);
}