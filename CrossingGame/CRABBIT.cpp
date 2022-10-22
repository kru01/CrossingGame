#include "CRABBIT.h"

CRABBIT::CRABBIT(int x, int y) : CANIMAL(x, y) {
	this->width = RABBIT_WIDTH;
	this->height = RABBIT_HEIGHT;
}

void CRABBIT::move() {
	x += fieldConstraints::HOR_SPEED - 1;

	if (x >= fieldConstraints::BOUND_RIGHT - RABBIT_WIDTH) {
		CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x + RABBIT_WIDTH, y + RABBIT_HEIGHT });
		isMoving = false;
		x = RABBIT_SPAWN_COORD.x;
		return;
	}

	CCONSOLE::eraseGraphics({ x - fieldConstraints::HOR_SPEED, y }, { x, y + RABBIT_HEIGHT });
	CCONSOLE::drawGraphics(RABBIT_SPRITE, { x, y }, RABBIT_COLOR);
}