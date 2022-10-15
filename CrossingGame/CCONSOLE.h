#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include "CCONSTANT.h"

using namespace std;

const HWND CONSOLE_WINDOW = GetConsoleWindow();
const HANDLE CONSOLE_STD_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
const int CONSOLE_BG_COLOR = colors::WHITE;

class CCONSOLE {
	static void resizeConsole(int width, int height);
	static void fixConsoleWindow();
	static void disableQuickEditMode();
	static void centerConsole();

public:
	static void initConsoleWindow();

	static void goToXY(int x, int y);
	static short isPressed(int);

	static void drawGraphics(string fileName, POINT coord, int color, int sleepTime = 0);
	static void eraseGraphics(POINT start, POINT end, int color = CONSOLE_BG_COLOR);
	static void setColor(int text, int background = CONSOLE_BG_COLOR);
};