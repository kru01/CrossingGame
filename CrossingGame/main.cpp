#include "CCONSOLE.h"
#include "CGAME.h"
#include "CENDSCREEN.h"

int main() {
	CCONSOLE console;
	console.initConsoleWindow();

	CENDSCREEN endScreen;
	CGAME* game = new CGAME(&endScreen);

	game->initGameGraphics();

	thread gameRunner(&CGAME::runGame, game);

	while (true) {
		if (!game->isRunning()) {
			if (endScreen.isPlayAgain()) {
				game->resetGame();
				gameRunner.join();
				gameRunner = thread(&CGAME::runGame, game);
				endScreen.clearChoice();

			} else if (endScreen.isToMenu()) {
				game->terminateGame(gameRunner);
				delete game;
				game = new CGAME(&endScreen);
				endScreen.clearChoice();

			} else if (endScreen.isExit()) {
				game->terminateGame(gameRunner);
				delete game;
				game = nullptr;
				return 0;
			}
		}
	}

	return 0;
}