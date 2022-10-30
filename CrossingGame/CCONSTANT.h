#pragma once
#include <vector>
#include <string>

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

const std::string FIELD_SPRITE = "assets/gameInterfaces/playfield.txt";
const int FIELD_WIDTH = 120, FIELD_HEIGHT = 38;
const int FIELD_COLOR = colors::BLACK;

enum fieldConstraints : int {
	BORDER_WIDTH = 1,
	ROAD_WIDTH = 5,

	HOR_SPEED = 3,
	VER_SPEED = ROAD_WIDTH + BORDER_WIDTH,

	HOR_OFFSET = 14,
	VER_OFFSET = 4,

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


const std::string GUIDEBOX_SPRITE = "assets/gameInterfaces/guideBox.txt";
const int GUIDEBOX_COLOR = colors::BLACK;

const std::string NUMBER_SPRITE = "assets/gameInterfaces/numbers/0.txt";
const int NUMBER_WIDTH = 5, NUMBER_HEIGHT = 4;

enum guideBoxConstraints : int {
	GUIDEBOX_XCOORD = fieldConstraints::HOR_OFFSET + FIELD_WIDTH + 5,
	GUIDEBOX_YCOORD = fieldConstraints::VER_OFFSET,

	LV_NUM_XCOORD = 22 + GUIDEBOX_XCOORD,
	LV_NUM_YCOORD = 1 + GUIDEBOX_YCOORD,

	GAME_STATUS_XCOORD = 16 + GUIDEBOX_XCOORD,
	GAME_STATUS_YCOORD = 7 + GUIDEBOX_YCOORD,

	TEXT_BOX_WIDTH = 30,
	TEXT_BOX_HEIGHT = 18,
	TEXT_BOX_XCOORD = 3 + GUIDEBOX_XCOORD,
	TEXT_BOX_YCOORD = 18 + GUIDEBOX_YCOORD
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