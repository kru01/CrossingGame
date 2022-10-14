#pragma once

class CPEOPLE {
	short X, Y;
	bool isAlive;

public:
	CPEOPLE() = default;
	CPEOPLE(short x, short y);

	bool isDead();
};