#include "CCONSOLE.h"
#include "CMAINMENU.h"
#include "CGAME.h"
#include "CENDSCREEN.h"

int main() {
	CCONSOLE console;
	console.initConsoleWindow();

	CMAINMENU mainMenu;
	CENDSCREEN endScreen;
	CGAME* game = new CGAME(&endScreen);
	bool isNewOrLoadGame = false;
	CCONSOLE::playSound("gameOn");

	while (true) {
		mainMenu.runMenu();

		if (mainMenu.isNewGame()) {
			game->initGameGraphics();
			isNewOrLoadGame = true;

		} else if (mainMenu.isLoadGame()) {
			mainMenu.drawLoadBox();
			if (game->loadGame(false)) isNewOrLoadGame = true;
			else Sleep(1500);

		} else if (mainMenu.isSetting()) {
			mainMenu.setGameLevel(game->getLevel());
			mainMenu.handleSetting();
			game->setLevel(mainMenu.getGameLevel());

		} else if (mainMenu.isAbout()) {
			mainMenu.handleAbout();

		} else if (mainMenu.isExit()) {
			delete game;
			game = nullptr;
			return 0;
		}
		
		mainMenu.clearChoice();
		CCONSOLE::flushKeyPressedAsync();
		if (!isNewOrLoadGame) continue;

		thread gameRunner(&CGAME::runGame, game);

		while (true) {
			if (!game->isPlayerDead()) {
				if (CCONSOLE::isToggledAsync('E'))
					if (!game->isRunning()) {
						game->resumeGame();
						gameRunner.join();
						gameRunner = thread(&CGAME::runGame, game);
					} else game->pauseGame();

				if (CCONSOLE::isToggledAsync('Q')) {
					Global_soundOn = !Global_soundOn;
					if (!Global_soundOn) CCONSOLE::stopAllSound();
					else CCONSOLE::playSound("background1", true);
				}

				if (CCONSOLE::isToggledAsync('Z')) {
					game->pauseGame();
					gameRunner.join();
					game->saveGame();
					game->resumeGame();
					gameRunner = thread(&CGAME::runGame, game);
				}

				if (CCONSOLE::isToggledAsync('X')) {
					game->pauseGame();
					gameRunner.join();
					game->loadGame(true);
					game->resumeGame();
					gameRunner = thread(&CGAME::runGame, game);
				}

				if (CCONSOLE::isToggledAsync('C')) {
					game->terminateGame(gameRunner);
					delete game;
					game = new CGAME(&endScreen);
					isNewOrLoadGame = false;
					CCONSOLE::stopAllSound();
					CCONSOLE::clearScreen();
					break;
				}

				if (CCONSOLE::isToggledAsync(VK_ESCAPE)) {
					game->terminateGame(gameRunner);
					delete game;
					game = nullptr;
					return 0;
				}

			} else if (!game->isRunning()) {
				if (endScreen.isPlayAgain()) {
					game->resetGame();
					gameRunner.join();
					gameRunner = thread(&CGAME::runGame, game);
					endScreen.clearChoice();

				} else if (endScreen.isToMenu()) {
					game->terminateGame(gameRunner);
					delete game;
					game = new CGAME(&endScreen);
					isNewOrLoadGame = false;
					endScreen.clearChoice();
					CCONSOLE::stopAllSound();
					CCONSOLE::clearScreen();
					break;

				} else if (endScreen.isExit()) {
					game->terminateGame(gameRunner);
					delete game;
					game = nullptr;
					return 0;
				}
			}
		}
	}

	return 0;
}