#pragma once
#include "CCONSOLE.h"
#include "CCONSTANT.h"

class CVEHICLE {
protected:
	int x, y;

public:
	CVEHICLE() = default;
	CVEHICLE(int x, int y);

	virtual void move() = 0;
};