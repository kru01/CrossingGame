#include "CBUS.h"

CBUS::CBUS(int x, int y) : CVEHICLE(x, y) {
	this->width = BUS_WIDTH;
	this->height = BUS_HEIGHT;
}

void CBUS::move() {
	if (isInRedLight) {
		CCONSOLE::drawGraphics(BUS_SPRITE, { x , y }, BUS_COLOR);
		return;
	}

	x -= fieldConstraints::HOR_SPEED;

	if (x <= fieldConstraints::BOUND_LEFT + TFLIGHT_WIDTH) {
		CCONSOLE::eraseGraphics({ x, y }, { x + BUS_WIDTH + fieldConstraints::HOR_SPEED, y + BUS_HEIGHT });
		isMoving = false;
		x = BUS_SPAWN_COORD.x;
		return; 
	}

	CCONSOLE::eraseGraphics({ x + BUS_WIDTH - 1, y }, { x + BUS_WIDTH + fieldConstraints::HOR_SPEED, y + BUS_HEIGHT });
	CCONSOLE::drawGraphics(BUS_SPRITE, { x, y }, BUS_COLOR);
}

void CBUS::makeSound() {
	CCONSOLE::playSound("vehicleHit");
}