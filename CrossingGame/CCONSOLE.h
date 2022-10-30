#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <random>
#include "CCONSTANT.h"

using namespace std;

const HWND CONSOLE_WINDOW = GetConsoleWindow();
const HANDLE CONSOLE_STD_INPUT = GetStdHandle(STD_INPUT_HANDLE);
const HANDLE CONSOLE_STD_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
const int CONSOLE_WIDTH_PX = 1400, CONSOLE_HEIGHT_PX = 800;
// Scroll all the way down to see CONSOLE's actual width and height (in character unit)
const int CONSOLE_TXT_COLOR = colors::BLACK;
const int CONSOLE_BG_COLOR = colors::WHITE;

class CCONSOLE {
	static void resizeAndCenterConsole(int width, int height);
	static void fixConsoleWindow();
	static void disableQuickEditMode();

public:
	static void initConsoleWindow();
	static int resizeCenterAndGetConsoleRowsCols(bool getRows);
	static void showConsoleCursor(bool flag);

	static void goToXY(int x, int y);
	static int getRandInt(const int min, const int max);
	static short isPressedAsync(int nVirtKey);
	static short isToggledAsync(int nVirtKey);
	static void flushKeyPressedAsync();
	static int getChArrowKeyPressed(int key);

	static void drawTexts(string text, POINT coord, int color, int background = CONSOLE_BG_COLOR);
	static void eraseTexts(POINT coord, int txtLength, int background = CONSOLE_BG_COLOR);
	static void drawGraphics(string fileName, POINT coord, int color, int background = CONSOLE_BG_COLOR, int sleepTime = 0);
	static void eraseGraphics(POINT start, POINT end, int background = CONSOLE_BG_COLOR);
	static void setColor(int text, int background = CONSOLE_BG_COLOR);
	static void clearScreen();
};

// 190 x 47
const int CONSOLE_WIDTH = CCONSOLE::resizeCenterAndGetConsoleRowsCols(false), CONSOLE_HEIGHT = CCONSOLE::resizeCenterAndGetConsoleRowsCols(true);