#pragma once
#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(short x, short y) {
	this->X = x;
	this->Y = y;
	this->isAlive = true;
}

bool CPEOPLE::isDead() {
	return !isAlive;
}