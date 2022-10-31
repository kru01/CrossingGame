#include "CMAINMENU.h"

CMAINMENU::CMAINMENU() {
	newGameChosen = loadGameChosen = settingChosen = aboutChosen = exitChosen = false;
	gameLevel = 1;
}

void CMAINMENU::drawMenu() {
	CCONSOLE::drawGraphics(CROSSING_TXT_SPRITE, { MENU_DRAW_POINT_COORD.x, MENU_DRAW_POINT_COORD.y - menuConstraints::MENU_TITLE_HEIGHT - menuConstraints::MENU_MARGIN }, MENU_COLOR);
	CCONSOLE::drawGraphics(GAME_TXT_SPRITE, { MENU_DRAW_POINT_COORD.x + CROSSING_TXT_WIDTH + menuConstraints::MENU_TITLE_GAP, MENU_DRAW_POINT_COORD.y - menuConstraints::MENU_TITLE_HEIGHT - menuConstraints::MENU_MARGIN }, MENU_SELECT_COLOR);
	CCONSOLE::drawGraphics(MENU_SPRITE, MENU_DRAW_POINT_COORD, MENU_COLOR);
	CCONSOLE::drawGraphics(ROAD_IMG_SPRITE, { MENU_DRAW_POINT_COORD.x, MENU_DRAW_POINT_COORD.y + menuConstraints::MENU_HEIGHT + menuConstraints::MENU_MARGIN }, ROAD_IMG_COLOR);
}

void CMAINMENU::drawInput(int currY) {
	for (int i = 0; i < MENU_OPTIONS.size(); i++) {
		const int optionYCoord = MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * i;

		if (currY != optionYCoord) CCONSOLE::drawTexts(MENU_OPTIONS[i], { MENU_FIRST_OPT_COORD.x, optionYCoord }, MENU_COLOR);
		else CCONSOLE::drawTexts(MENU_OPTIONS[i], { MENU_FIRST_OPT_COORD.x, optionYCoord }, MENU_COLOR, MENU_SELECT_COLOR);
	}
}

void CMAINMENU::handleEnter(int currY) {
	if (currY == MENU_FIRST_OPT_COORD.y) newGameChosen = true;
	else if (currY == MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP) loadGameChosen = true;
	else if (currY == MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * 2) settingChosen = true;
	else if (currY == MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * 3) aboutChosen = true;
	else if (currY == MENU_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * 4) exitChosen = true;
}

void CMAINMENU::handleInput() {
	int key = 0, currY = MENU_FIRST_OPT_COORD.y;
	drawInput(currY);

	while (true) {
		key = toupper(_getch());
		key = CCONSOLE::getChArrowKeyPressed(key);

		switch (key) {
		case 'W':
			if (currY > MENU_FIRST_OPT_COORD.y) currY -= menuConstraints::MENU_OPTION_GAP;
			else currY = MENU_LAST_OPT_COORD.y;
			drawInput(currY);
			break;
		case 'S':
			if (currY < MENU_LAST_OPT_COORD.y) currY += menuConstraints::MENU_OPTION_GAP;
			else currY = MENU_FIRST_OPT_COORD.y;
			drawInput(currY);
		}

		if (key == VK_RETURN) {
			handleEnter(currY);
			return;
		}
	}
}

void CMAINMENU::drawSetting() {
	CCONSOLE::drawGraphics(SETTING_SPRITE, SETTING_DRAW_COORD, SETTING_BOX_COLOR);
	CCONSOLE::drawGraphics(SETTING_SYMBOL_SPRITE, SETTING_SYMBOL_COORD, SETTING_SYMBOL_COLOR);
	drawLevelNum();
	CCONSOLE::drawTexts("ON", {SETTING_SYMBOL_COORD.x + menuConstraints::SETTING_SYMBOL_GAP, SETTING_SYMBOL_COORD.y + menuConstraints::SETTING_SYMBOL_GAP }, colors::GREEN);
}

void CMAINMENU::drawSettingInput(int currY) {
	for (int i = 0; i < SETTING_OPTIONS.size(); i++) {
		const int optionYCoord = SETTING_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP * i;

		if (currY != optionYCoord) CCONSOLE::drawTexts(SETTING_OPTIONS[i], { SETTING_FIRST_OPT_COORD.x, optionYCoord }, SETTING_BOX_COLOR);
		else CCONSOLE::drawTexts(SETTING_OPTIONS[i], { SETTING_FIRST_OPT_COORD.x, optionYCoord }, SETTING_BOX_COLOR, MENU_SELECT_COLOR);
	}
}

void CMAINMENU::drawLevelNum() {
	string num = to_string(gameLevel);
	if (gameLevel < 10) num.insert(0, 1, '0');
	CCONSOLE::drawTexts(num, { SETTING_SYMBOL_COORD.x + menuConstraints::SETTING_SYMBOL_GAP, SETTING_SYMBOL_COORD.y }, colors::RED);
}

void CMAINMENU::setLevel(bool isLeft) {
	if (isLeft) {
		gameLevel--;
		gameLevel = !gameLevel ? MAX_GAME_LV : gameLevel;
	} else gameLevel = gameLevel % MAX_GAME_LV + 1;

	drawLevelNum();
}

void CMAINMENU::toggleSound(bool isLeft) {
	
}

void CMAINMENU::runMenu() {
	FlushConsoleInputBuffer(CONSOLE_STD_INPUT);
	drawMenu();
	handleInput();
}

void CMAINMENU::drawLoadBox() {
	CCONSOLE::drawGraphics(LOAD_BOX_SPRITE, MENU_DRAW_POINT_COORD, LOAD_BOX_COLOR);
}

void CMAINMENU::handleSetting() {
	drawSetting();
	int key = 0, currY = SETTING_FIRST_OPT_COORD.y;
	drawSettingInput(currY);

	while (true) {
		key = toupper(_getch());
		key = CCONSOLE::getChArrowKeyPressed(key);

		switch (key) {
		case 'W':
			if (currY > SETTING_FIRST_OPT_COORD.y) currY -= menuConstraints::MENU_OPTION_GAP;
			else currY = SETTING_LAST_OPT_COORD.y;
			drawSettingInput(currY);
			break;
		case 'S':
			if (currY < SETTING_LAST_OPT_COORD.y) currY += menuConstraints::MENU_OPTION_GAP;
			else currY = SETTING_FIRST_OPT_COORD.y;
			drawSettingInput(currY);
			break;
		case 'A':
			if (currY == SETTING_FIRST_OPT_COORD.y) setLevel(true);
			if (currY == SETTING_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP) toggleSound(true);
			break;
		case 'D':
			if (currY == SETTING_FIRST_OPT_COORD.y) setLevel(false);
			if (currY == SETTING_FIRST_OPT_COORD.y + menuConstraints::MENU_OPTION_GAP) toggleSound(false);
		}

		if (key == VK_RETURN && currY == SETTING_LAST_OPT_COORD.y)
			return;
	}
}

void CMAINMENU::handleAbout() {
	drawLoadBox();
	CCONSOLE::drawGraphics(ABOUT_SPRITE, LOAD_BOX_COORD, LOAD_BOX_TXT_COLOR);
	CCONSOLE::drawTexts("Back", { LOAD_BOX_COORD.x, LOAD_BOX_COORD.y + menuConstraints::ABOUT_BACK_BASE_Y }, LOAD_BOX_COLOR, MENU_SELECT_COLOR);
	int key = 0;
	while (true) {
		key = _getch();
		switch (key) {
		case 'Q':
		case 'q':
		case VK_RETURN:
		case VK_ESCAPE:
		case VK_BACK:
		case VK_SPACE:
			return;
		}
	}
}

void CMAINMENU::clearChoice() {
	newGameChosen = loadGameChosen = settingChosen = aboutChosen = exitChosen = false;
}

bool CMAINMENU::isNewGame() {
	return newGameChosen;
}

bool CMAINMENU::isLoadGame() {
	return loadGameChosen;
}

bool CMAINMENU::isSetting() {
	return settingChosen;
}

bool CMAINMENU::isAbout() {
	return aboutChosen;
}

bool CMAINMENU::isExit() {
	return exitChosen;
}

int CMAINMENU::getGameLevel() {
	return gameLevel;
}

void CMAINMENU::setGameLevel(int gameLevel) {
	this->gameLevel = gameLevel;
}