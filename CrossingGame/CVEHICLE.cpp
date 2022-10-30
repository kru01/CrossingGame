#include "CVEHICLE.h"

CVEHICLE::CVEHICLE(int x, int y) {
	this->x = x;
	this->y = y;
	this->width = this->height = 0;
	this->isMoving = false;
	this->isInRedLight = false;
}

int CVEHICLE::getX() {
	return x;
}

int CVEHICLE::getY() {
	return y;
}

void CVEHICLE::setX(int x) {
	this->x = x;
}

void CVEHICLE::setY(int y) {
	this->y = y;
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

void CVEHICLE::setRedLight(bool flag) {
	isInRedLight = flag;
}

bool CVEHICLE::isRedLight() {
	return isInRedLight;
}