#pragma once
#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(int x, int y) {
	this->x = x;
	this->y = y;
	this->isAlive = true;
}

void CPEOPLE::goUp() {
	if (y <= fieldConstraints::BOUND_TOP) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	y -= fieldConstraints::VER_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { x, y }, 0);
}

void CPEOPLE::goDown() {
	if (y >= fieldConstraints::BOUND_BOTTOM) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	y += fieldConstraints::VER_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { x, y }, 0);
}

void CPEOPLE::goLeft() {
	if (x <= fieldConstraints::BOUND_LEFT) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	x -= fieldConstraints::HOR_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { x, y }, 0);
}

void CPEOPLE::goRight() {
	if (x >= fieldConstraints::BOUND_RIGHT - HUMAN_WIDTH) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	x += fieldConstraints::HOR_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { x, y }, 0);
}

bool CPEOPLE::isDead() {
	return !isAlive;
}

POINT CPEOPLE::getCoord() {
	return { x, y };
}