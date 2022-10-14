#pragma once
#include "CCONSOLE.h"
#include "CPEOPLE.h"
#include "CCONSTANT.h"

class CGAME {
	CPEOPLE player;

	void updatePosOfPeople();
public:
	CGAME();

	static void initGame();
	void runGame();
};