#pragma once
#include "CCONSOLE.h"

const string MENU_SPRITE = "assets/mainMenu/menu.txt";
const int MENU_COLOR = colors::AQUA;
const int MENU_SELECT_COLOR = colors::LIGHT_YELLOW;

const string CROSSING_TXT_SPRITE = "assets/mainMenu/crossing.txt";
const string GAME_TXT_SPRITE = "assets/mainMenu/game.txt";
const int CROSSING_TXT_WIDTH = 63;

const string ROAD_IMG_SPRITE = "assets/mainMenu/road.txt";
const int ROAD_IMG_COLOR = colors::YELLOW;

const string LOAD_BOX_SPRITE = "assets/mainMenu/loadInterface.txt";
const int LOAD_BOX_COLOR = colors::BLUE;
const int LOAD_BOX_TXT_COLOR = colors::BLACK;

const string SETTING_SPRITE = "assets/mainMenu/setting.txt";
const string SETTING_SYMBOL_SPRITE = "assets/mainMenu/settingSymbols.txt";
const int SETTING_BOX_COLOR = colors::BLUE;
const int SETTING_SYMBOL_COLOR = colors::BLACK;

const string ABOUT_SPRITE = "assets/mainMenu/about.txt";

const vector<string> MENU_OPTIONS = {
	"NEW GAME",
	"LOAD GAME",
	"SETTING",
	"ABOUT",
	"EXIT GAME"
};

const vector<string> SETTING_OPTIONS = {
	"Level",
	"Sound",
	"Confirm"
};

enum menuConstraints : int {
	MENU_WIDTH = 100,
	MENU_HEIGHT = 28,

	MENU_FIRST_OPT_BASE_X = 46,
	MENU_FIRST_OPT_BASE_Y = 15,
	MENU_OPTION_GAP = 2,

	MENU_TITLE_HEIGHT = 6,
	MENU_TITLE_GAP = 5,
	MENU_MARGIN = 1,

	LOAD_BOX_BASE_X = 27,
	LOAD_BOX_BASE_Y = 4,

	SETTING_BOX_WIDTH = 53,
	SETTING_BOX_HEIGHT = 9,

	SETTING_FIRST_OPT_BASE_X = 19,
	SETTING_FIRST_OPT_BASE_Y = 2,
	SETTING_SYMBOL_BASE_X = 28,
	SETTING_SYMBOL_GAP = 2,

	ABOUT_BACK_BASE_Y = 8
};

const POINT MENU_DRAW_POINT_COORD = { CONSOLE_WIDTH / 2 - menuConstraints::MENU_WIDTH / 2, CONSOLE_HEIGHT / 2 - menuConstraints::MENU_HEIGHT / 2 };
const POINT MENU_FIRST_OPT_COORD = { menuConstraints::MENU_FIRST_OPT_BASE_X + MENU_DRAW_POINT_COORD.x, menuConstraints::MENU_FIRST_OPT_BASE_Y + MENU_DRAW_POINT_COORD.y };
const POINT MENU_LAST_OPT_COORD = { MENU_FIRST_OPT_COORD.x, MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * (MENU_OPTIONS.size() - 1)};

const POINT SETTING_DRAW_COORD = { (menuConstraints::MENU_WIDTH - menuConstraints::SETTING_BOX_WIDTH) / 2 + MENU_DRAW_POINT_COORD.x, MENU_FIRST_OPT_COORD.y };
const POINT SETTING_FIRST_OPT_COORD = { menuConstraints::SETTING_FIRST_OPT_BASE_X + SETTING_DRAW_COORD.x, menuConstraints::SETTING_FIRST_OPT_BASE_Y + SETTING_DRAW_COORD.y };
const POINT SETTING_LAST_OPT_COORD = { SETTING_FIRST_OPT_COORD.x, SETTING_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * (SETTING_OPTIONS.size() - 1) };
const POINT SETTING_SYMBOL_COORD = { menuConstraints::SETTING_SYMBOL_BASE_X + SETTING_DRAW_COORD.x, SETTING_FIRST_OPT_COORD.y };

const POINT LOAD_BOX_COORD = { menuConstraints::LOAD_BOX_BASE_X + MENU_DRAW_POINT_COORD.x, menuConstraints::LOAD_BOX_BASE_Y + MENU_DRAW_POINT_COORD.y };

class CMAINMENU {
	bool newGameChosen, loadGameChosen, settingChosen, aboutChosen, exitChosen;
	int gameLevel;

	static void drawMenu();
	static void drawInput(int currY);
	void handleEnter(int currY);
	void handleInput();

	void drawSetting();
	static void drawSettingInput(int currY);
	void drawLevelNum();
	void setLevel(bool isLeft);
	void drawSoundState();
	void toggleSound();

public:
	CMAINMENU();

	void runMenu();
	static void drawLoadBox();
	void handleSetting();
	static void handleAbout();

	void clearChoice();
	bool isNewGame();
	bool isLoadGame();
	bool isSetting();
	bool isAbout();
	bool isExit();

	int getGameLevel();
	void setGameLevel(int gameLevel);
};