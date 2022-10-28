#pragma once
#include <vector>

enum fieldConstraints : int {
	BORDER_WIDTH = 1,
	ROAD_WIDTH = 5,

	HOR_SPEED = 3,
	VER_SPEED = ROAD_WIDTH + BORDER_WIDTH,

	HOR_OFFSET = 5,
	VER_OFFSET = 3,

	F_TOP = 1 + BORDER_WIDTH + VER_OFFSET,
	F_BOTTOM = 37 - BORDER_WIDTH + VER_OFFSET,
	F_LEFT = 4 + BORDER_WIDTH + HOR_OFFSET,
	F_RIGHT = 116 - BORDER_WIDTH + HOR_OFFSET,

	BOUND_TOP = F_TOP + VER_SPEED,
	BOUND_BOTTOM = F_BOTTOM - VER_SPEED,
	BOUND_LEFT = F_LEFT + HOR_SPEED,
	BOUND_RIGHT = F_RIGHT - HOR_SPEED
};

// The lanes that objects can spawn on, ordered from top to bottom
const std::vector<int> LANE_YCOORD = {
	fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED * 3,
	fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED * 2,
	fieldConstraints::BOUND_BOTTOM - fieldConstraints::VER_SPEED,
	fieldConstraints::BOUND_BOTTOM
};

enum colors : int {
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE
};

enum vehicles : int {
	CAR,
	BUS
};

enum arrowKeys : int {
	NUMLOCK_ENABLED = 0,
	NUMLOCK_DISABLED = 224,
	ARROW_UP = 72,
	ARROW_DOWN = 80,
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77
};