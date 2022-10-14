#include "CCONSOLE.h"
#include "CGAME.h"

int main() {
	CCONSOLE console;
	console.initConsoleWindow();

	CGAME* game = new CGAME;
	game->initGame();
	game->runGame();

	return 0;
}