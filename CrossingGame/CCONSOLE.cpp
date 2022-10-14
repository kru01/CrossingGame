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

short CCONSOLE::isPressed(int nVirtKey) {
	return GetAsyncKeyState(nVirtKey) & 0x01;
}

void CCONSOLE::drawGraphics(string fileName, COORD coord, int color, int sleepTime) {
	ifstream infile(fileName);

	if (!infile.good()) {
		cerr << "No file found!";
		return;
	}

	string buffer;

	while (getline(infile, buffer)) {
		Sleep(sleepTime);
		goToXY(coord.X, coord.Y);
		cout << buffer;
		coord.Y++;
	}

	infile.close();
}

void CCONSOLE::eraseGraphics(POINT start, POINT end) {
	string eraser(end.x - start.x + 1, ' ');
	for (int i = start.y; i < end.y; i++) {
		goToXY(start.x, i);
		cout << eraser;
	}
}