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
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { x, y }, HUMAN_COLOR);
}

void CPEOPLE::goDown() {
	if (y >= fieldConstraints::BOUND_BOTTOM) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	y += fieldConstraints::VER_SPEED;
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { x, y }, HUMAN_COLOR);
}

void CPEOPLE::goLeft() {
	if (x <= fieldConstraints::BOUND_LEFT) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	x -= fieldConstraints::HOR_SPEED;
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { x, y }, HUMAN_COLOR);
}

void CPEOPLE::goRight() {
	if (x >= fieldConstraints::BOUND_RIGHT - HUMAN_WIDTH) return;
	CCONSOLE::eraseGraphics({ x, y }, { x + HUMAN_WIDTH, y + HUMAN_HEIGHT });
	x += fieldConstraints::HOR_SPEED;
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { x, y },HUMAN_COLOR);
}

bool CPEOPLE::isImpact(CVEHICLE* obj) {
	return x >= obj->getX() - HUMAN_WIDTH && x <= obj->getX() + obj->getWidth()
		&& y >= obj->getY() && y <= obj->getY() + obj->getHeight();
}

bool CPEOPLE::isImpact(CANIMAL* obj) {
	return x >= obj->getX() - HUMAN_WIDTH && x <= obj->getX() + obj->getWidth()
		&& y >= obj->getY() && y <= obj->getY() + obj->getHeight();
}

void CPEOPLE::setDead(bool flag) {
	isAlive = !flag;
}

bool CPEOPLE::isDead() {
	return !isAlive;
}

int CPEOPLE::getX() {
	return x;
}

int CPEOPLE::getY() {
	return y;
}