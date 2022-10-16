#pragma once
#include "CANIMAL.h"

CANIMAL::CANIMAL(int x, int y) {
	this->x = x;
	this->y = y;
	this->width = this->height = 0;
	this->isMoving = true;
}

int CANIMAL::getX() {
	return x;
}

int CANIMAL::getY() {
	return y;
}

int CANIMAL::getWidth() {
	return width;
}

int CANIMAL::getHeight() {
	return height;
}

void CANIMAL::setMove(bool flag) {
	isMoving = flag;
}

bool CANIMAL::canMove() {
	return isMoving;
}