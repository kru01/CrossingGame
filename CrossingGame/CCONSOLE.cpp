#pragma once
#include "CCONSOLE.h"

void CCONSOLE::setWindowDimension(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT rec;
	GetWindowRect(console, &rec);
	MoveWindow(console, rec.left, rec.top, width, height, true);
}

void CCONSOLE::fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	long style = GetWindowLongW(consoleWindow, GWL_STYLE);
	style = style & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;
	SetWindowLongW(consoleWindow, GWL_STYLE, style);
}

void CCONSOLE::initConsoleWindow() {
	setWindowDimension(1400, 800);
	fixConsoleWindow();
	SetConsoleOutputCP(65001);
}

void CCONSOLE::goToXY(short x, short y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}