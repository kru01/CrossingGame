#pragma once
#include "CVEHICLE.h"

CVEHICLE::CVEHICLE(int x, int y) {
	this->x = x;
	this->y = y;
	this->width = this->height = 0;
	this->isMoving = true;
}

int CVEHICLE::getX() {
	return x;
}

int CVEHICLE::getY() {
	return y;
}

int CVEHICLE::getWidth() {
	return width;
}

int CVEHICLE::getHeight() {
	return height;
}

void CVEHICLE::setMove(bool flag) {
	isMoving = flag;
}

bool CVEHICLE::canMove() {
	return isMoving;
}