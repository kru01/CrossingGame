#include "CGAME.h"

CGAME::CGAME(CENDSCREEN* endScreen) {
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);

	for (int i = 0; i < OBJECT_LIMIT; i++) {
		carsVect.push_back(new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y));
		busesVect.push_back(new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y));
		rabbitsVect.push_back(new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y));
		catsVect.push_back(new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y));
	}

	tfLightCars = CTRAFFICLIGHT(20, 10);
	tfLightBuses = CTRAFFICLIGHT(15, 10);
	this->endScreen = endScreen;

	level = 1;
	isInProgress = true;
}

CGAME::~CGAME() {
	for (int i = 0; i < OBJECT_LIMIT; i++) {
		delete carsVect[i], carsVect[i] = nullptr;
		delete busesVect[i], busesVect[i] = nullptr;
		delete rabbitsVect[i], rabbitsVect[i] = nullptr;
		delete catsVect[i], catsVect[i] = nullptr;
	}

	for (int i = 0; i < humansVect.size(); i++)
		delete humansVect[i], humansVect[i] = nullptr;

	delete player, player = nullptr;
	endScreen = nullptr;
}

template<class Obj>
bool CGAME::isValidDistance(Obj*& obj1, Obj*& obj2) {
	return abs(obj1->getX() - obj2->getX()) >= OBJECT_GAP + obj1->getWidth();
}

void CGAME::updatePosPeople() {
	if (CCONSOLE::isPressedAsync('W') || CCONSOLE::isPressedAsync(VK_UP)) player->goUp();
	if (CCONSOLE::isPressedAsync('S') || CCONSOLE::isPressedAsync(VK_DOWN)) player->goDown();
	if (CCONSOLE::isPressedAsync('A') || CCONSOLE::isPressedAsync(VK_LEFT)) player->goLeft();
	if (CCONSOLE::isPressedAsync('D') || CCONSOLE::isPressedAsync(VK_RIGHT)) player->goRight();
}

void CGAME::updatePosVehicle() {
	updatePosObject(carsVect);
	updatePosObject(busesVect);
}

void CGAME::updatePosAnimal() {
	updatePosObject(rabbitsVect);
	updatePosObject(catsVect);
}

template<class Obj>
void CGAME::updatePosObject(vector<Obj*>& objVect) {
	for (int i = 0; i < objVect.size(); i++) {
		if (objVect[i]->canMove()) {
			objVect[i]->move();
			if (player->isImpact(objVect[i])) player->setDead(true);
			continue;
		}

		for (int j = 0; j < objVect.size(); j++)
			if (i != j)
				if (objVect[j]->canMove()) {
					if (!isValidDistance(objVect[i], objVect[j])) {
						objVect[i]->setMove(false);
						break;
					}
				} else objVect[i]->setMove(true);
	}
}

bool CGAME::checkImpactPeopleAndDrawEffect() {
	bool impacted = false;

	for (auto& human : humansVect)
		if (player->isImpact(human)) {
			impacted = true;
			impactPeopleEffect(human);
		}

	return impacted;
}

void CGAME::impactPeopleEffect(CPEOPLE*& victim) {
	player->setY(player->getY() + fieldConstraints::VER_SPEED);
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_COLOR);

	for (auto& human : humansVect)
		CCONSOLE::drawGraphics(HUMAN_SPRITE, { human->getX(), human->getY() }, (human != victim ? HUMAN_COLOR : HUMAN_HIT_COLOR));

	const int remarkPos = CCONSOLE::getRandInt(0, HUMAN_REMARKS.size() - 1);
	CCONSOLE::drawTexts(HUMAN_REMARKS[remarkPos], { victim->getX(), victim->getY() - REMARKS_OFFSET }, HUMAN_HIT_COLOR);
	Sleep(EFFECT_DURATION);
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { victim->getX(), victim->getY() }, HUMAN_COLOR);
	CCONSOLE::eraseTexts({ victim->getX(), victim->getY() - REMARKS_OFFSET }, HUMAN_REMARKS[remarkPos].length());
}

void CGAME::playerWinEffect() {
	for (int i = 0; i < EFFECT_LOOP; i++) {
		for (auto& human : humansVect) CCONSOLE::drawGraphics(HUMAN_CHEER_SPRITE, { human->getX(), human->getY() }, HUMAN_CHEER_COLOR);
		Sleep(EFFECT_DURATION);
		for (auto& human : humansVect) CCONSOLE::drawGraphics(HUMAN_SPRITE, { human->getX(), human->getY() }, HUMAN_COLOR);
		Sleep(EFFECT_DURATION);
	}
}

void CGAME::playerDeadEffect() {
	for (int i = 0; i < EFFECT_LOOP; i++) {
		CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_HIT_COLOR);
		Sleep(EFFECT_DURATION);
		CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_COLOR, HUMAN_HIT_COLOR);
		Sleep(EFFECT_DURATION);
	}
}

bool CGAME::advanceLevel() {
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);

	if (level == 5) {
		player->setDead(true);
		playerWinEffect();
		runGameWon();
		return false;
	}

	CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_COLOR);
	
	level++;
	string levelText = "level ";
	levelText.push_back(level + 48);
	CCONSOLE::drawTexts(levelText, { fieldConstraints::F_RIGHT + 10, fieldConstraints::F_TOP - 5 }, colors::BLACK);
	return true;
}

void CGAME::runGameOver() {
	CCONSOLE::clearScreen();
	isInProgress = false;
	endScreen->runEndScreen(true);
}

void CGAME::runGameWon() {
	CCONSOLE::clearScreen();
	isInProgress = false;
	endScreen->runEndScreen(false);
}

void CGAME::renewObjects() {
	for (int i = 0; i < OBJECT_LIMIT; i++) {
		delete carsVect[i];
		carsVect[i] = new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y);

		delete busesVect[i];
		busesVect[i] = new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y);

		delete rabbitsVect[i];
		rabbitsVect[i] = new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y);

		delete catsVect[i];
		catsVect[i] = new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y);
	}

	for (int i = 0; i < humansVect.size(); i++)
		delete humansVect[i], humansVect[i] = nullptr;

	humansVect.clear();
	delete player;
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);
}

void CGAME::initGameGraphics() {
	CCONSOLE::clearScreen();
	CCONSOLE::drawGraphics(FIELD_SPRITE, { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, FIELD_COLOR);
	CCONSOLE::drawTexts("level 1", {fieldConstraints::F_RIGHT + 10, fieldConstraints::F_TOP - 5}, colors::BLACK);
}

void CGAME::runGame() {
	while (isInProgress) {
		tfLightCars.updateLightStatus(carsVect, vehicles::CAR);
		tfLightBuses.updateLightStatus(busesVect, vehicles::BUS);
		
		if (!player->isDead()) {
			CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_COLOR);
			updatePosPeople();
		}

		updatePosVehicle();
		updatePosAnimal();

		if (player->isDead()) {
			playerDeadEffect();
			runGameOver();
			return;
		}

		if (player->isAtFinishLine())
			if (!checkImpactPeopleAndDrawEffect()) {
				for (auto& human : humansVect) CCONSOLE::drawGraphics(HUMAN_SPRITE, { human->getX(), human->getY() }, HUMAN_COLOR);
				humansVect.push_back(player);
				if (!advanceLevel()) return;
			}

		Sleep(300);
	}
}

void CGAME::resetGame() {
	renewObjects();
	level = 1;
	initGameGraphics();
	isInProgress = true;
}

void CGAME::terminateGame(thread& gameRunner) {
	CCONSOLE::clearScreen();
	isInProgress = false;
	gameRunner.join();
}

bool CGAME::isRunning() {
	return isInProgress;
}