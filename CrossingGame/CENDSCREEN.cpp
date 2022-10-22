#include "CENDSCREEN.h"

CENDSCREEN::CENDSCREEN() {
	playAgainChosen = toMenuChosen = exitChosen = false;
}

void CENDSCREEN::drawEndscreen(bool isGameOver) {
	if (isGameOver) CCONSOLE::drawGraphics(GAME_OVER_SPRITE, ES_DRAW_POINT_COORD, ES_COLOR);
	else CCONSOLE::drawGraphics(GAME_WIN_SPRITE, ES_DRAW_POINT_COORD, ES_COLOR);
}

void CENDSCREEN::drawInput(int currY) {
	CCONSOLE::drawTexts(FIRST_OPT, ES_FIRST_OPT_COORD, ES_COLOR);
	CCONSOLE::drawTexts(SECOND_OPT, { ES_FIRST_OPT_COORD.x, ES_FIRST_OPT_COORD.y + OPTION_GAP }, ES_COLOR);
	CCONSOLE::drawTexts(THIRD_OPT, { ES_FIRST_OPT_COORD.x, ES_FIRST_OPT_COORD.y + OPTION_GAP * 2 }, ES_COLOR);

	if (currY == ES_FIRST_OPT_COORD.y) CCONSOLE::drawTexts(FIRST_OPT, ES_FIRST_OPT_COORD, ES_COLOR, ES_SELECT_COLOR);
	else if (currY == ES_FIRST_OPT_COORD.y + OPTION_GAP) CCONSOLE::drawTexts(SECOND_OPT, { ES_FIRST_OPT_COORD.x, ES_FIRST_OPT_COORD.y + OPTION_GAP }, ES_COLOR, ES_SELECT_COLOR);
	else if (currY == ES_FIRST_OPT_COORD.y + OPTION_GAP * 2) CCONSOLE::drawTexts(THIRD_OPT, { ES_FIRST_OPT_COORD.x, ES_FIRST_OPT_COORD.y + OPTION_GAP * 2 }, ES_COLOR, ES_SELECT_COLOR);
}

void CENDSCREEN::handleEnter(int currY) {
	if (currY == ES_FIRST_OPT_COORD.y) playAgainChosen = true;
	else if (currY == ES_FIRST_OPT_COORD.y + OPTION_GAP) toMenuChosen = true;
	else if (currY == ES_FIRST_OPT_COORD.y + OPTION_GAP * 2) exitChosen = true;
}

void CENDSCREEN::handleInput() {
	int key = 0, currY = ES_FIRST_OPT_COORD.y;
	drawInput(currY);

	while (true) {
		key = toupper(_getch());

		switch (key) {
		case 'W':
			if (currY > ES_FIRST_OPT_COORD.y) currY -= 2;
			else currY = ES_LAST_OPT_COORD.y;
			drawInput(currY);
			break;
		case 'S':
			if (currY < ES_LAST_OPT_COORD.y) currY += 2;
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