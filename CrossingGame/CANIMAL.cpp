#include "CANIMAL.h"

CANIMAL::CANIMAL(int x, int y) {
	this->x = x;
	this->y = y;
	this->width = this->height = 0;
	this->isMoving = false;
}

int CANIMAL::getX() {
	return x;
}

int CANIMAL::getY() {
	return y;
}

void CANIMAL::setX(int x) {
	this->x = x;
}

void CANIMAL::setY(int y) {
	this->y = y;
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