#pragma once
#include "CCONSOLE.h"

void CCONSOLE::resizeConsole(int width, int height) {
	RECT rec;
	GetWindowRect(CONSOLE_WINDOW, &rec);
	MoveWindow(CONSOLE_WINDOW, rec.left, rec.top, width, height, true);
}

void CCONSOLE::fixConsoleWindow() {
	long style = GetWindowLongW(CONSOLE_WINDOW, GWL_STYLE);
	style = style & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;
	SetWindowLongW(CONSOLE_WINDOW, GWL_STYLE, style);
}

void CCONSOLE::initConsoleWindow() {
	resizeConsole(1400, 800);
	fixConsoleWindow();
	system("color 70");
	SetConsoleOutputCP(65001);
}

void CCONSOLE::goToXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(CONSOLE_STD_OUTPUT, coord);
}

short CCONSOLE::isPressed(int nVirtKey) {
	return GetAsyncKeyState(nVirtKey) & 0x01;
}

void CCONSOLE::drawGraphics(string fileName, POINT coord, int color, int sleepTime) {
	ifstream infile(fileName);

	if (!infile.good()) {
		cerr << "No file found!";
		return;
	}

	setColor(color);
	string buffer;

	while (getline(infile, buffer)) {
		Sleep(sleepTime);
		goToXY(coord.x, coord.y);
		cout << buffer;
		coord.y++;
	}

	infile.close();
}

void CCONSOLE::eraseGraphics(POINT start, POINT end, int color) {
	setColor(color);
	string eraser(end.x - start.x, ' ');
	for (int i = start.y; i < end.y; i++) {
		goToXY(start.x, i);
		cout << eraser;
	}
}

void CCONSOLE::setColor(int colorCode) {
	SetConsoleTextAttribute(CONSOLE_STD_OUTPUT, colorCode);
}