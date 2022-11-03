#include "CCONSOLE.h"

bool Global_soundOn = true;

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

void CCONSOLE::getSoundPath(string& sound) {
	string path = SOUND_PATH;
	path.insert(path.size() - 4, sound);
	sound = path;
}

void CCONSOLE::initConsoleWindow() {
	// resizeAndCenterConsole is called in resizeCenterAndGetConsoleRowsCols
	// This is lowkey stupid but it's the only way to init CONSOLE_WIDTH and CONSOLE_HEIGHT at runtime
	SetConsoleTitleA("HCMUS - 21CLC05 - Team 2 | Crossing Game");
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

void CCONSOLE::showConsoleCursor(bool flag) {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(CONSOLE_STD_OUTPUT, &cursorInfo);
}

void CCONSOLE::goToXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(CONSOLE_STD_OUTPUT, coord);
}

int CCONSOLE::getRandInt(const int min, const int max) {
	static thread_local random_device rd;
	static thread_local mt19937 generator(rd());
	uniform_int_distribution<int> distInt(min, max);
	return distInt(generator);
}

short CCONSOLE::isPressedAsync(int nVirtKey) {
	// GetAsyncKeyState will leave keys in the buffer
	// Try FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); if you encounter weird input behaviors
	return GetAsyncKeyState(nVirtKey);
}

short CCONSOLE::isToggledAsync(int nVirtKey) {
	return GetAsyncKeyState(nVirtKey) & 0x01;
}

// This is beyond dumb, refer to this https://stackoverflow.com/questions/36870063/how-to-flush-or-clear-getasynckeystates-buffer
void CCONSOLE::flushKeyPressedAsync() {
	isPressedAsync('W');
	isPressedAsync('S');
	isPressedAsync('A');
	isPressedAsync('D');
	isPressedAsync(VK_UP);
	isPressedAsync(VK_DOWN);
	isPressedAsync(VK_LEFT);
	isPressedAsync(VK_RIGHT);
	isToggledAsync('E');
	isToggledAsync('Q');
	isToggledAsync('Z');
	isToggledAsync('X');
	isToggledAsync('C');
	isToggledAsync(VK_ESCAPE);
}

// https://stackoverflow.com/questions/10463201/getch-and-arrow-codes
int CCONSOLE::getChArrowKeyPressed(int key) {
	if (key != arrowKeys::NUMLOCK_ENABLED && key != arrowKeys::NUMLOCK_DISABLED) return key;
	key = _getch();
	switch (key) {
	case arrowKeys::ARROW_UP: return 'W';
	case arrowKeys::ARROW_DOWN: return 'S';
	case arrowKeys::ARROW_LEFT: return 'A';
	case arrowKeys::ARROW_RIGHT: return 'D';
	}
	return key;
}

void CCONSOLE::drawTexts(string text, POINT coord, int color, int background) {
	goToXY(coord.x, coord.y);
	setColor(color, background);
	cout << text;
}

void CCONSOLE::eraseTexts(POINT coord, int txtLength, int background) {
	string eraser(txtLength, ' ');
	goToXY(coord.x, coord.y);
	setColor(background, background);
	cout << eraser;
}

void CCONSOLE::drawGraphics(string fileName, POINT coord, int color, int background, int sleepTime) {
	ifstream infile(fileName);

	if (!infile.good()) {
		cerr << "No file found!";
		return;
	}

	string buffer;
	setColor(color, background);

	while (getline(infile, buffer)) {
		Sleep(sleepTime);
		goToXY(coord.x, coord.y);
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

void CCONSOLE::playSound(string sound, bool isLoop) {
	if (!Global_soundOn) return;
	getSoundPath(sound);
	if (isLoop) PlaySoundA(sound.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else PlaySoundA(sound.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void CCONSOLE::stopAllSound() {
	PlaySoundA(NULL, NULL, NULL);
}