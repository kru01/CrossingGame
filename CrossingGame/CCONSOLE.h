#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

class CCONSOLE {
	static void setWindowDimension(int width, int height);
	static void fixConsoleWindow();

public:
	static void initConsoleWindow();

	static void goToXY(short x, short y);
	static short isPressed(int);

	static void drawGraphics(string fileName, COORD coord, int color, int sleepTime = 0);
	static void eraseGraphics(POINT start, POINT end);
};