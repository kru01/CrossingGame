#include "CCONSOLE.h"

void CCONSOLE::resizeAndCenterConsole(int width, int height) {
	RECT rectWindow;
	GetWindowRect(CONSOLE_WINDOW, &rectWindow);
	int posX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int posY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
	MoveWindow(CONSOLE_WINDOW, posX, posY, width, height, true);
}

void CCONSOLE::fixConsoleWindow() {
	long style = GetWindowLongW(CONSOLE_WINDOW, GWL_STYLE);
	style = style & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME;
	SetWindowLongW(CONSOLE_WINDOW, GWL_STYLE, style);
}

void CCONSOLE::disableQuickEditMode() {
	DWORD prevMode;
	GetConsoleMode(CONSOLE_STD_INPUT, &prevMode);
	SetConsoleMode(CONSOLE_STD_INPUT, ENABLE_EXTENDED_FLAGS | (prevMode & ~ENABLE_QUICK_EDIT_MODE));
}

void CCONSOLE::showConsoleCursor(bool flag) {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(CONSOLE_STD_OUTPUT, &cursorInfo);
}

void CCONSOLE::initConsoleWindow() {
	// resizeAndCenterConsole is called in resizeCenterAndGetConsoleRowsCols
	// This is lowkey stupid but it's the only way to init CONSOLE_WIDTH and CONSOLE_HEIGHT at runtime
	fixConsoleWindow();
	system("color 70");
	SetConsoleOutputCP(65001);
	disableQuickEditMode();
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);
	showConsoleCursor(false);
}

int CCONSOLE::resizeCenterAndGetConsoleRowsCols(bool getRows) {
	resizeAndCenterConsole(CONSOLE_WIDTH_PX, CONSOLE_HEIGHT_PX);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(CONSOLE_STD_OUTPUT, &csbi);
	if (getRows) return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void CCONSOLE::goToXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(CONSOLE_STD_OUTPUT, coord);
}

short CCONSOLE::isPressed(int nVirtKey) {
	// GetAsyncKeyState will leave keys in the buffer
	// Try FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); if you encounter weird input behaviors
	return GetAsyncKeyState(nVirtKey) & 0x01;
}

void CCONSOLE::drawTexts(string text, POINT coord, int color, int background) {
	goToXY(coord.x, coord.y);
	setColor(color, background);
	cout << text;
}

void CCONSOLE::drawGraphics(string fileName, POINT coord, int color, int background, int sleepTime) {
	ifstream infile(fileName);

	if (!infile.good()) {
		cerr << "No file found!";
		return;
	}

	string buffer;

	while (getline(infile, buffer)) {
		Sleep(sleepTime);
		goToXY(coord.x, coord.y);
		setColor(color, background);
		cout << buffer;
		coord.y++;
	}

	infile.close();
}

void CCONSOLE::eraseGraphics(POINT start, POINT end, int background) {
	setColor(background, background);
	string eraser(end.x - start.x, ' ');
	for (int i = start.y; i < end.y; i++) {
		goToXY(start.x, i);
		cout << eraser;
	}
}

void CCONSOLE::setColor(int text, int background) {
	SetConsoleTextAttribute(CONSOLE_STD_OUTPUT, background * 16 + text);
}

void CCONSOLE::clearScreen() {
	setColor(CONSOLE_TXT_COLOR, CONSOLE_BG_COLOR);
	system("cls");
}