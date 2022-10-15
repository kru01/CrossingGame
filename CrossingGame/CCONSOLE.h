#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

const HWND CONSOLE_WINDOW = GetConsoleWindow();
const HANDLE CONSOLE_STD_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);

class CCONSOLE {
	static void resizeConsole(int width, int height);
	static void fixConsoleWindow();

public:
	static void initConsoleWindow();

	static void goToXY(int x, int y);
	static short isPressed(int);

	static void drawGraphics(string fileName, POINT coord, int color, int sleepTime = 0);
	static void eraseGraphics(POINT start, POINT end, int color = 112);
	static void setColor(int colorCode);
};