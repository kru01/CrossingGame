#include "CCAT.h"

CCAT::CCAT(int x, int y) : CANIMAL(x, y) {
	this->width = CAT_WIDTH;
	this->height = CAT_HEIGHT;
}

void CCAT::move() {
	x -= fieldConstraints::HOR_SPEED + 1;

	if (x <= fieldConstraints::BOUND_LEFT) {
		CCONSOLE::eraseGraphics({ x, y }, { x + CAT_WIDTH + fieldConstraints::HOR_SPEED + 1, y + CAT_HEIGHT });
		isMoving = false;
		x = CAT_SPAWN_COORD.x;
		return;
	}

	CCONSOLE::eraseGraphics({ x + CAT_WIDTH - 1, y }, { x + CAT_WIDTH + fieldConstraints::HOR_SPEED + 1, y + CAT_HEIGHT });
	CCONSOLE::drawGraphics(CAT_SPRITE, { x, y }, CAT_COLOR);
}

void CCAT::makeSound() {
	CCONSOLE::playSound("catHit");
}