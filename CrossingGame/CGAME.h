#pragma once
#include "CCONSOLE.h"
#include "CPEOPLE.h"
#include "CCAR.h"
#include "CCONSTANT.h"

class CGAME {
	CPEOPLE player;
	CCAR car;

	void updatePosPeople();

	template<class Obj>
	void updatePosObject(Obj* obj);

public:
	CGAME();

	static void initGame();
	void runGame();
};