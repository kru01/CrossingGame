#include "CGAME.h"

CGAME::CGAME(CENDSCREEN* endScreen) {
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);

	for (int i = 0; i < OBJECT_ONSCREEN_LIMIT; i++) {
		carsVect.push_back(new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y));
		busesVect.push_back(new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y));
		rabbitsVect.push_back(new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y));
		catsVect.push_back(new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y));
	}

	for (const auto& entry : filesystem::directory_iterator{ SAVEFILE_PATH }) {
		if (savesSet.size() >= SAVEFILE_LIMIT) break;
		const auto& entryPath = entry.path();

		if (entry.is_regular_file() && entryPath.extension().string() == SAVEFILE_EXTENSION) {
			string fileName = entryPath.stem().string();
			decapitalizeString(fileName);
			savesSet.insert(fileName);
		}
	}

	tfLightCars = CTRAFFICLIGHT(vehicles::CAR);
	tfLightBuses = CTRAFFICLIGHT(vehicles::BUS);
	this->endScreen = endScreen;

	level = 1;
	isInProgress = true;
}

CGAME::~CGAME() {
	for (int i = 0; i < OBJECT_ONSCREEN_LIMIT; i++) {
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
			if (player->isImpact(objVect[i])) {
				player->setDead(true);
				objVect[i]->makeSound();
			}
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
			human->makeSound();
			impactPeopleEffect(human);
			CCONSOLE::playSound("background2", true);
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
	Sleep(EFFECT_DURATION + 50);
	CCONSOLE::drawGraphics(HUMAN_SPRITE, { victim->getX(), victim->getY() }, HUMAN_COLOR);
	CCONSOLE::eraseTexts({ victim->getX(), victim->getY() - REMARKS_OFFSET }, HUMAN_REMARKS[remarkPos].length());
}

void CGAME::playerWinEffect() {
	CCONSOLE::playSound("gameWon");
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

void CGAME::clearLane(int lane) {
	CCONSOLE::eraseGraphics({ fieldConstraints::BOUND_LEFT, lane - fieldConstraints::ROAD_WIDTH + fieldConstraints::BORDER_WIDTH }, { fieldConstraints::BOUND_RIGHT, lane });
}

void CGAME::clearAllLane() {
	for (auto& lane : LANE_YCOORD) clearLane(lane);
}

void CGAME::assignLaneRandomly() {
	vector<int> laneAssigner, availableLane = LANE_YCOORD;
	
	while (!availableLane.empty()) {
		const int lane = CCONSOLE::getRandInt(0, availableLane.size() - 1);
		laneAssigner.push_back(availableLane[lane]);
		availableLane.erase(availableLane.begin() + lane);
	}

	clearAllLane();

	for (auto& car : carsVect) car->setY(laneAssigner[0] - CAR_HEIGHT);
	tfLightCars.eraseTFLightAndFixBoard(vehicles::CAR);
	tfLightCars.setY(CTRAFFICLIGHT::calcTFLightYCoord(laneAssigner[0]));

	for (auto& bus : busesVect) bus->setY(laneAssigner[1] - BUS_HEIGHT);
	tfLightBuses.eraseTFLightAndFixBoard(vehicles::BUS);
	tfLightBuses.setY(CTRAFFICLIGHT::calcTFLightYCoord(laneAssigner[1]));

	for (auto& rabbit : rabbitsVect) rabbit->setY(laneAssigner[2] - RABBIT_HEIGHT);
	for (auto& cat : catsVect) cat->setY(laneAssigner[3] - CAT_HEIGHT);
}

void CGAME::drawGameStatus(bool isRunning) {
	CCONSOLE::drawTexts((isRunning ? "RUNNING" : "PAUSING"), { guideBoxConstraints::GAME_STATUS_XCOORD, guideBoxConstraints::GAME_STATUS_YCOORD }, GUIDEBOX_COLOR);
}

void CGAME::drawLevelNum(int level) {
	CCONSOLE::eraseGraphics({ guideBoxConstraints::LV_NUM_XCOORD, guideBoxConstraints::LV_NUM_YCOORD }, { guideBoxConstraints::LV_NUM_XCOORD + NUMBER_WIDTH * 2, guideBoxConstraints::LV_NUM_YCOORD + NUMBER_HEIGHT });
	string lvNum = "", numSprite = NUMBER_SPRITE;

	if (level < 10) lvNum.push_back('0');
	lvNum += to_string(level);

	numSprite[numSprite.size() - 5] = lvNum[0]; // -5 is the spot right before .txt
	CCONSOLE::drawGraphics(numSprite, { guideBoxConstraints::LV_NUM_XCOORD, guideBoxConstraints::LV_NUM_YCOORD }, GUIDEBOX_COLOR);
	numSprite[numSprite.size() - 5] = lvNum[1];
	CCONSOLE::drawGraphics(numSprite, { guideBoxConstraints::LV_NUM_XCOORD + NUMBER_WIDTH, guideBoxConstraints::LV_NUM_YCOORD }, GUIDEBOX_COLOR);
}

void CGAME::drawHumansVect() {
	for (auto& human : humansVect)
		CCONSOLE::drawGraphics(HUMAN_SPRITE, { human->getX(), human->getY() }, HUMAN_COLOR);
}

void CGAME::eraseTextBoxContent() {
	CCONSOLE::eraseGraphics({ guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD }, { guideBoxConstraints::TEXT_BOX_XCOORD + guideBoxConstraints::TEXT_BOX_WIDTH, guideBoxConstraints::TEXT_BOX_YCOORD + guideBoxConstraints::TEXT_BOX_HEIGHT });
}

bool CGAME::advanceLevel() {
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);

	if (level == MAX_GAME_LV) {
		player->setDead(true);
		playerWinEffect();
		runGameWon();
		return false;
	}

	CCONSOLE::drawGraphics(HUMAN_SPRITE, { player->getX(), player->getY() }, HUMAN_COLOR);
	assignLaneRandomly();

	level++;
	drawLevelNum(level);
	return true;
}

void CGAME::runGameOver() {
	CCONSOLE::clearScreen();
	isInProgress = false;
	CCONSOLE::playSound("gameOver");
	endScreen->runEndScreen(true);
}

void CGAME::runGameWon() {
	CCONSOLE::clearScreen();
	isInProgress = false;
	endScreen->runEndScreen(false);
}

void CGAME::renewObjects() {
	for (int i = 0; i < OBJECT_ONSCREEN_LIMIT; i++) {
		delete carsVect[i];
		carsVect[i] = new CCAR(CAR_SPAWN_COORD.x, CAR_SPAWN_COORD.y);

		delete busesVect[i];
		busesVect[i] = new CBUS(BUS_SPAWN_COORD.x, BUS_SPAWN_COORD.y);

		delete rabbitsVect[i];
		rabbitsVect[i] = new CRABBIT(RABBIT_SPAWN_COORD.x, RABBIT_SPAWN_COORD.y);

		delete catsVect[i];
		catsVect[i] = new CCAT(CAT_SPAWN_COORD.x, CAT_SPAWN_COORD.y);
	}

	tfLightCars.setY(TFLIGHT_CAR_LANE_COORD.y);
	tfLightBuses.setY(TFLIGHT_BUS_LANE_COORD.y);

	for (int i = 0; i < humansVect.size(); i++)
		delete humansVect[i], humansVect[i] = nullptr;

	humansVect.clear();
	delete player;
	player = new CPEOPLE(HUMAN_SPAWN_COORD.x, HUMAN_SPAWN_COORD.y);
}

void CGAME::getSavefilePath(string& savefile) {
	savefile += SAVEFILE_EXTENSION;
	savefile = SAVEFILE_PATH + savefile;
}

void CGAME::listSavefile(bool isInGame) {
	POINT drawCoord = { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD };
	int color = GUIDEBOX_COLOR;

	if (!isInGame) {
		drawCoord = LOAD_BOX_COORD;
		color = LOAD_BOX_TXT_COLOR;
	} 

	CCONSOLE::eraseGraphics(drawCoord, { drawCoord.x + guideBoxConstraints::TEXT_BOX_WIDTH, drawCoord.y + SAVEFILE_LIMIT + 1 });
	CCONSOLE::drawTexts("Savefiles: oldest to newest", drawCoord, color);
	string filename = "";

	int index = 1;
	for (auto& save : savesSet) {
		filename = to_string(index);
		filename += ". ";
		filename += save;
		CCONSOLE::drawTexts(filename, { drawCoord.x, drawCoord.y + index }, color);
		filename = "";
		index++;
	}
}

void CGAME::decapitalizeString(string& str) {
	transform(str.begin(), str.end(), str.begin(), [](char& ch) {
		return tolower(ch);
		});
}

void CGAME::standardizeFilename(string& filename) {
	if (filename.size() > SAVEFILE_MAX_LENGTH) filename.erase(SAVEFILE_MAX_LENGTH - 1);

	filename.erase(remove_if(filename.begin(), filename.end(), [](const char& c) {
		return !isalnum(c);
		}), filename.end());

	if (filename.empty()) filename = "blank";
	else decapitalizeString(filename);
}

string CGAME::promptSavefileName(bool isInGame) {
	POINT drawCoord = { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD };
	int color = GUIDEBOX_COLOR;

	if (!isInGame) {
		drawCoord = LOAD_BOX_COORD;
		color = LOAD_BOX_TXT_COLOR;
	}

	CCONSOLE::drawTexts("Input savefile's name:", { drawCoord.x, drawCoord.y + SAVEFILE_LIMIT + 1 }, color);
	
	FlushConsoleInputBuffer(CONSOLE_STD_INPUT);
	CCONSOLE::goToXY(drawCoord.x, drawCoord.y + SAVEFILE_LIMIT + 2);
	CCONSOLE::showConsoleCursor(true);
	string buffer;
	cin >> buffer;
	CCONSOLE::showConsoleCursor(false);
	cin.ignore(cin.rdbuf()->in_avail()); // refer to https://cplusplus.com/forum/beginner/178692/
	CCONSOLE::flushKeyPressedAsync();

	standardizeFilename(buffer);
	return buffer;
}

template<class Obj>
void CGAME::writeObjectToFile(ofstream& fout, const vector<Obj*>& objVect) {
	int x = 0, y = 0;
	bool canMove = false;

	for (int i = 0; i < OBJECT_ONSCREEN_LIMIT; i++) {
		x = objVect[i]->getX();
		y = objVect[i]->getY();
		canMove = objVect[i]->canMove();
		fout.write(reinterpret_cast<const char*>(&x), sizeof(x));
		fout.write(reinterpret_cast<const char*>(&y), sizeof(y));
		fout.write(reinterpret_cast<const char*>(&canMove), sizeof(canMove));
	}
}

template<class Obj>
void CGAME::writeTFLightToFile(ofstream& fout, Obj& tfLight) {
	int x = tfLight.getX(), y = tfLight.getY();
	bool isRed = tfLight.isRedLight();
	int greenTime = tfLight.getGreenTime(), redTime = tfLight.getRedTime(), timeElapsed = tfLight.getTimeElapsed();

	fout.write(reinterpret_cast<const char*>(&x), sizeof(x));
	fout.write(reinterpret_cast<const char*>(&y), sizeof(y));
	fout.write(reinterpret_cast<const char*>(&isRed), sizeof(isRed));
	fout.write(reinterpret_cast<const char*>(&greenTime), sizeof(greenTime));
	fout.write(reinterpret_cast<const char*>(&redTime), sizeof(redTime));
	fout.write(reinterpret_cast<const char*>(&timeElapsed), sizeof(timeElapsed));
}

template<class Obj>
void CGAME::readObjectFromFile(ifstream& fin, vector<Obj*>& objVect) {
	int x = 0, y = 0;
	bool canMove = false;

	for (int i = 0; i < OBJECT_ONSCREEN_LIMIT; i++) {
		fin.read(reinterpret_cast<char*>(&x), sizeof(x));
		fin.read(reinterpret_cast<char*>(&y), sizeof(y));
		fin.read(reinterpret_cast<char*>(&canMove), sizeof(canMove));
		objVect[i]->setX(x);
		objVect[i]->setY(y);
		objVect[i]->setMove(canMove);
	}
}

template<class Obj>
void CGAME::readTFLightFromFile(ifstream& fin, Obj& tfLight) {
	int x = 0, y = 0;
	bool isRed = false;
	int greenTime = 0, redTime = 0, timeElapsed = 0;
	
	fin.read(reinterpret_cast<char*>(&x), sizeof(x));
	fin.read(reinterpret_cast<char*>(&y), sizeof(y));
	fin.read(reinterpret_cast<char*>(&isRed), sizeof(isRed));
	fin.read(reinterpret_cast<char*>(&greenTime), sizeof(greenTime));
	fin.read(reinterpret_cast<char*>(&redTime), sizeof(redTime));
	fin.read(reinterpret_cast<char*>(&timeElapsed), sizeof(timeElapsed));

	tfLight.setX(x);
	tfLight.setY(y);
	tfLight.setGreenTime(greenTime);
	tfLight.setRedTime(redTime);
	tfLight.setTimeElapsed(timeElapsed);
	tfLight.setLight(isRed);
}

void CGAME::populateHumansVect() {
	set<int> randomXCoords;
	for (auto& human : humansVect) {
		if (!randomXCoords.insert(human->getX()).second) continue;
		for (int i = human->getX() - HUMAN_WIDTH; i < human->getX(); i++)
			randomXCoords.insert(i);
	}

	while (humansVect.size() < level - 1) {
		const int randX = CCONSOLE::getRandInt(fieldConstraints::BOUND_LEFT, fieldConstraints::BOUND_RIGHT - HUMAN_WIDTH);
		if(abs(randX - HUMAN_SPAWN_COORD.x) % fieldConstraints::HOR_SPEED != 0 || !randomXCoords.insert(randX).second)
			continue;
		
		for (int i = randX - HUMAN_WIDTH; i < randX; i++)
			randomXCoords.insert(i);

		humansVect.push_back(new CPEOPLE(randX, fieldConstraints::F_TOP + 1));
	}
}

void CGAME::initGameGraphics() {
	CCONSOLE::clearScreen();
	CCONSOLE::drawGraphics(FIELD_SPRITE, { fieldConstraints::HOR_OFFSET, fieldConstraints::VER_OFFSET }, FIELD_COLOR);
	CCONSOLE::drawGraphics(GUIDEBOX_SPRITE, { guideBoxConstraints::GUIDEBOX_XCOORD, guideBoxConstraints::GUIDEBOX_YCOORD }, GUIDEBOX_COLOR);
	drawLevelNum(level);
	drawGameStatus(true);
	drawHumansVect();
}

void CGAME::runGame() {
	CCONSOLE::playSound("background1", true);
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

		Sleep(RENDER_SPEED);
	}
}

void CGAME::resetGame() {
	renewObjects();
	level = 1;
	initGameGraphics();
	isInProgress = true;
	CCONSOLE::flushKeyPressedAsync();
}

void CGAME::terminateGame(thread& gameRunner) {
	CCONSOLE::clearScreen();
	isInProgress = false;
	gameRunner.join();
}

void CGAME::resumeGame() {
	isInProgress = true;
	drawGameStatus(true);
}

void CGAME::pauseGame() {
	isInProgress = false;
	drawGameStatus(false);
}

void CGAME::saveGame() {
	eraseTextBoxContent();
	listSavefile(true);
	string outfile = promptSavefileName(true);

	if (savesSet.size() + 1 > SAVEFILE_LIMIT) {
		string topmostFile = *savesSet.begin();
		savesSet.erase(topmostFile);
		getSavefilePath(topmostFile);
		filesystem::remove(topmostFile);
	}

	savesSet.insert(outfile);
	listSavefile(true);

	getSavefilePath(outfile);
	ofstream fout(outfile, ios::binary | ios::trunc);
	if (fout.fail()) {
		CCONSOLE::drawTexts("Unable to create savefile!", { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD + SAVEFILE_LIMIT + 3 }, GUIDEBOX_COLOR);
		return;
	}

	fout.write(reinterpret_cast<const char*>(&level), sizeof(level));
	writeObjectToFile(fout, carsVect);
	writeObjectToFile(fout, busesVect);
	writeObjectToFile(fout, rabbitsVect);
	writeObjectToFile(fout, catsVect);

	int x = player->getX(), y = player->getY();
	bool isDead = player->isDead();
	fout.write(reinterpret_cast<const char*>(&x), sizeof(x));
	fout.write(reinterpret_cast<const char*>(&y), sizeof(y));
	fout.write(reinterpret_cast<const char*>(&isDead), sizeof(isDead));

	int humanSize = humansVect.size();
	fout.write(reinterpret_cast<const char*>(&humanSize), sizeof(humanSize));
	for (int i = 0; i < humanSize; i++) {
		x = humansVect[i]->getX();
		y = humansVect[i]->getY();
		fout.write(reinterpret_cast<const char*>(&x), sizeof(x));
		fout.write(reinterpret_cast<const char*>(&y), sizeof(y));
	}

	writeTFLightToFile(fout, tfLightCars);
	writeTFLightToFile(fout, tfLightBuses);
	fout.close();
	CCONSOLE::playSound("fileSave");
	CCONSOLE::drawTexts("Saved successfully!", { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD + SAVEFILE_LIMIT + 4 }, GUIDEBOX_COLOR);
}

bool CGAME::loadGame(bool isInGame) {
	eraseTextBoxContent();
	listSavefile(isInGame);

	POINT errorCoord = { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD };
	int color = GUIDEBOX_COLOR;

	if (!isInGame) {
		errorCoord = LOAD_BOX_COORD;
		color = LOAD_BOX_TXT_COLOR;
	}

	if (savesSet.empty()) {
		CCONSOLE::drawTexts("No savefile available!", { errorCoord.x, errorCoord.y + SAVEFILE_LIMIT + 3 }, color);
		return false;
	}

	string infile = promptSavefileName(isInGame);
	getSavefilePath(infile);
	ifstream fin(infile, ios::binary);

	if (fin.fail()) {
		CCONSOLE::drawTexts("No such savefile exists!", { errorCoord.x, errorCoord.y + SAVEFILE_LIMIT + 3 }, color);
		return false;
	}

	fin.read(reinterpret_cast<char*>(&level), sizeof(level));
	readObjectFromFile(fin, carsVect);
	readObjectFromFile(fin, busesVect);
	readObjectFromFile(fin, rabbitsVect);
	readObjectFromFile(fin, catsVect);

	int x = 0, y = 0;
	bool isDead = false;
	fin.read(reinterpret_cast<char*>(&x), sizeof(x));
	fin.read(reinterpret_cast<char*>(&y), sizeof(y));
	fin.read(reinterpret_cast<char*>(&isDead), sizeof(isDead));
	player->setX(x);
	player->setY(y);
	player->setDead(isDead);

	int humanSize = 0;
	fin.read(reinterpret_cast<char*>(&humanSize), sizeof(humanSize));

	for (int i = 0; i < humansVect.size(); i++)
		delete humansVect[i], humansVect[i] = nullptr;
	humansVect.clear();

	for (int i = 0; i < humanSize; i++) {
		fin.read(reinterpret_cast<char*>(&x), sizeof(x));
		fin.read(reinterpret_cast<char*>(&y), sizeof(y));
		humansVect.push_back(new CPEOPLE(x, y));
	}

	readTFLightFromFile(fin, tfLightCars);
	readTFLightFromFile(fin, tfLightBuses);
	fin.close();

	CCONSOLE::playSound("fileLoad");
	initGameGraphics();
	CCONSOLE::drawTexts("Savefile loaded successfully!", { guideBoxConstraints::TEXT_BOX_XCOORD, guideBoxConstraints::TEXT_BOX_YCOORD + guideBoxConstraints::TEXT_BOX_HEIGHT - 1 }, GUIDEBOX_COLOR);
	return true;
}

int CGAME::getLevel() {
	return level;
}

void CGAME::setLevel(int level) {
	this->level = level;
	populateHumansVect();
}

bool CGAME::isRunning() {
	return isInProgress;
}

bool CGAME::isPlayerDead() {
	return player->isDead();
}