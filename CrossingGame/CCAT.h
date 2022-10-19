#pragma once
#include "CCONSTANT.h"
#include "CANIMAL.h"

const string CAT_SPRITE = "assets/objects/cat.txt";
const int CAT_WIDTH = 9, CAT_HEIGHT = 4;
const int CAT_COLOR = colors::BLACK;
const POINT CAT_SPAWN_COORD = { fieldConstraints::BOUND_RIGHT - CAT_WIDTH, fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED - CAT_HEIGHT };

class CCAT : public CANIMAL {
public:
	CCAT() = default;
	CCAT(int x, int y);

	void move();
};