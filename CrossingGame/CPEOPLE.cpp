#pragma once
#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(short x, short y) {
	this->X = x;
	this->Y = y;
	this->width = this->height = 3;
	this->isAlive = true;
}

void CPEOPLE::goUp() {
	if (Y <= fieldConstraints::TOP + fieldConstraints::ROAD_WIDTH) return;
	CCONSOLE::eraseGraphics({ X, Y }, { X + width, Y + height });
	Y -= fieldConstraints::ROAD_WIDTH;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { X, Y }, 0);
}

void CPEOPLE::goDown() {
	if (Y >= fieldConstraints::BOTTOM - fieldConstraints::ROAD_WIDTH) return;
	CCONSOLE::eraseGraphics({ X, Y }, { X + width, Y + height });
	Y += fieldConstraints::ROAD_WIDTH;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { X, Y }, 0);
}

void CPEOPLE::goLeft() {
	if (X <= fieldConstraints::LEFT) return;
	CCONSOLE::eraseGraphics({ X, Y }, { X + width, Y + height });
	X -= fieldConstraints::HORIZONTAL_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { X, Y }, 0);
}

void CPEOPLE::goRight() {
	if (X >= fieldConstraints::RIGHT) return;
	CCONSOLE::eraseGraphics({ X, Y }, { X + width, Y + height });
	X += fieldConstraints::HORIZONTAL_SPEED;
	CCONSOLE::drawGraphics("assets/objects/human.txt", { X, Y }, 0);
}

bool CPEOPLE::isDead() {
	return !isAlive;
}

COORD CPEOPLE::getCoord() {
	return { X, Y };
}

int CPEOPLE::getWidth() {
	return width;
}