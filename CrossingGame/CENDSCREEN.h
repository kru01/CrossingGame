#pragma once
#include "CCONSOLE.h"

const string GAME_WIN_SPRITE = "assets/gameInterfaces/gameWin.txt";
const string GAME_OVER_SPRITE = "assets/gameInterfaces/gameOver.txt";
const int ES_SELECT_COLOR = colors::LIGHT_YELLOW;
const int ES_COLOR = colors::AQUA;

const vector<string> ES_OPTIONS = {
	"PLAY AGAIN",
	"BACK TO MENU",
	"EXIT GAME"
};

enum endScreenConstraints : int {
	ES_WIDTH = 100,
	ES_HEIGHT = 23,
	ES_FIRST_OPT_BASE_X = 45,
	ES_FIRST_OPT_BASE_Y = 14,
	ES_OPTION_GAP = 2,
};

const POINT ES_DRAW_POINT_COORD = { CONSOLE_WIDTH / 2 - endScreenConstraints::ES_WIDTH / 2, CONSOLE_HEIGHT / 2 - endScreenConstraints::ES_HEIGHT / 2 };
const POINT ES_FIRST_OPT_COORD = { endScreenConstraints::ES_FIRST_OPT_BASE_X + ES_DRAW_POINT_COORD.x, endScreenConstraints::ES_FIRST_OPT_BASE_Y + ES_DRAW_POINT_COORD.y - 1};
const POINT ES_LAST_OPT_COORD = { ES_FIRST_OPT_COORD.x, ES_FIRST_OPT_COORD.y + endScreenConstraints::ES_OPTION_GAP * (ES_OPTIONS.size() - 1)};

class CENDSCREEN {
	bool playAgainChosen, toMenuChosen, exitChosen;

	static void drawEndscreen(bool isGameOver);
	static void drawInput(int currY);
	void handleEnter(int currY);
	void handleInput();

public:
	CENDSCREEN();

	void runEndScreen(bool isGameOver);
	void clearChoice();

	bool isPlayAgain();
	bool isToMenu();
	bool isExit();
};