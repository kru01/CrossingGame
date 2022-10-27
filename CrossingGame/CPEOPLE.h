#pragma once
#include <vector>
#include "CCONSOLE.h"
#include "CCONSTANT.h"
#include "CVEHICLE.h"
#include "CANIMAL.h"
#include "CTRAFFICLIGHT.h"

const string HUMAN_SPRITE = "assets/objects/human.txt";
const int HUMAN_WIDTH = 3, HUMAN_HEIGHT = 3;
const int HUMAN_COLOR = colors::BLACK, HUMAN_HIT_COLOR = colors::RED;
const POINT HUMAN_SPAWN_COORD = { (fieldConstraints::F_RIGHT + fieldConstraints::F_LEFT) / 2 - HUMAN_WIDTH, fieldConstraints::F_BOTTOM - HUMAN_HEIGHT };
const vector<string> HUMAN_REMARKS = { "Hey, I'm standin' here!", "Watch where you're going!", "Oi, watch it man!", "Go away dude!", "Ay what's yo problem!?" };
const int REMARKS_OFFSET = HUMAN_HEIGHT + fieldConstraints::BORDER_WIDTH;

class CPEOPLE {
	int x, y;
	bool isAlive;

public:
	CPEOPLE() = default;
	CPEOPLE(int x, int y);

	void goUp();
	void goDown();
	void goLeft();
	void goRight();

	bool isImpact(CVEHICLE* obj);
	bool isImpact(CANIMAL* obj);
	bool isImpact(CPEOPLE* human);

	void setDead(bool flag);
	bool isDead();
	bool isAtFinishLine();
	
	int getX();
	int getY();
	void setY(int y);
};