#pragma once
#include <iostream>
#include <Windows.h>

class CCONSOLE {
	static void setWindowDimension(int width, int height);
	static void fixConsoleWindow();

public:
	static void initConsoleWindow();
	static void goToXY(short x, short y);
};