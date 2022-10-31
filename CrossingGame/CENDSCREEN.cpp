#include "CENDSCREEN.h"

CENDSCREEN::CENDSCREEN() {
	playAgainChosen = toMenuChosen = exitChosen = false;
}

void CENDSCREEN::drawEndscreen(bool isGameOver) {
	if (isGameOver) CCONSOLE::drawGraphics(GAME_OVER_SPRITE, ES_DRAW_POINT_COORD, ES_COLOR);
	else CCONSOLE::drawGraphics(GAME_WIN_SPRITE, ES_DRAW_POINT_COORD, ES_COLOR);
}

void CENDSCREEN::drawInput(int currY) {
	for (int i = 0; i < ES_OPTIONS.size(); i++) {
		const int optionYCoord = ES_FIRST_OPT_COORD.y + endScreenConstraints::ES_OPTION_GAP * i;

		if (currY != optionYCoord) CCONSOLE::drawTexts(ES_OPTIONS[i], { ES_FIRST_OPT_COORD.x, optionYCoord }, ES_COLOR);
		else CCONSOLE::drawTexts(ES_OPTIONS[i], { ES_FIRST_OPT_COORD.x, optionYCoord }, ES_COLOR, ES_SELECT_COLOR);
	}
}

void CENDSCREEN::handleEnter(int currY) {
	if (currY == ES_FIRST_OPT_COORD.y) playAgainChosen = true;
	else if (currY == ES_FIRST_OPT_COORD.y + endScreenConstraints::ES_OPTION_GAP) toMenuChosen = true;
	else if (currY == ES_FIRST_OPT_COORD.y + endScreenConstraints::ES_OPTION_GAP * 2) exitChosen = true;
}

void CENDSCREEN::handleInput() {
	int key = 0, currY = ES_FIRST_OPT_COORD.y;
	drawInput(currY);

	while (true) {
		key = toupper(_getch());
		key = CCONSOLE::getChArrowKeyPressed(key);

		switch (key) {
		case 'W':
			if (currY > ES_FIRST_OPT_COORD.y) currY -= endScreenConstraints::ES_OPTION_GAP;
			else currY = ES_LAST_OPT_COORD.y;
			drawInput(currY);
			break;
		case 'S':
			if (currY < ES_LAST_OPT_COORD.y) currY += endScreenConstraints::ES_OPTION_GAP;
			else currY = ES_FIRST_OPT_COORD.y;
			drawInput(currY);
		}

		if (key == VK_RETURN) {
			handleEnter(currY);
			return;
		}
	}
}

void CENDSCREEN::runEndScreen(bool isGameOver) {
	FlushConsoleInputBuffer(CONSOLE_STD_INPUT);
	drawEndscreen(isGameOver);
	handleInput();
}

void CENDSCREEN::clearChoice() {
	playAgainChosen = toMenuChosen = exitChosen = false;
}

bool CENDSCREEN::isPlayAgain() {
	return playAgainChosen;
}

bool CENDSCREEN::isToMenu() {
	return toMenuChosen;
}

bool CENDSCREEN::isExit() {
	return exitChosen;
}