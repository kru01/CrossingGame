#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(int vehicle) {
	this->x = this->y = 0;
	this->greenTime = this->redTime = 0;

	switch (vehicle) {
	case vehicles::CAR:
		this->x = TFLIGHT_CAR_LANE_COORD.x;
		this->y = TFLIGHT_CAR_LANE_COORD.y;
		this->greenTime = CCONSOLE::getRandInt(20, 25);
		this->redTime = CCONSOLE::getRandInt(10, 20);
		break;
	case vehicles::BUS:
		this->x = TFLIGHT_BUS_LANE_COORD.x;
		this->y = TFLIGHT_BUS_LANE_COORD.y;
		this->greenTime = CCONSOLE::getRandInt(10, 20);
		this->redTime = CCONSOLE::getRandInt(15, 20);
	}

	this->isRed = false;
	this->timeElapsed = 0;
}

void CTRAFFICLIGHT::updateSprite(int& lane) {
	if (isRed) {
		switch (lane) {
		case vehicles::CAR:
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y }, colors::BLACK);
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y + 1 }, colors::RED);
			break;
		case vehicles::BUS:
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y }, colors::BLACK);
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y + 1 }, colors::RED);
		}

		return;
	}

	switch (lane) {
	case vehicles::CAR:
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y }, colors::GREEN);
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y + 1 }, colors::BLACK);
		break;
	case vehicles::BUS:
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y }, colors::GREEN);
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { x, y + 1 }, colors::BLACK);
	}
}

int CTRAFFICLIGHT::getX() {
	return x;
}

int CTRAFFICLIGHT::getY() {
	return y;
}

int CTRAFFICLIGHT::getGreenTime() {
	return greenTime;
}

int CTRAFFICLIGHT::getRedTime() {
	return redTime;
}

int CTRAFFICLIGHT::getTimeElapsed() {
	return timeElapsed;
}

bool CTRAFFICLIGHT::isRedLight() {
	return isRed;
}

void CTRAFFICLIGHT::setX(int x) {
	this->x = x;
}

void CTRAFFICLIGHT::setY(int y) {
	this->y = y;
}

void CTRAFFICLIGHT::setGreenTime(int greenTime) {
	this->greenTime = greenTime;
}

void CTRAFFICLIGHT::setRedTime(int redTime) {
	this->redTime = redTime;
}

void CTRAFFICLIGHT::setTimeElapsed(int timeElapsed) {
	this->timeElapsed = timeElapsed;
}

void CTRAFFICLIGHT::setLight(bool isRed) {
	this->isRed = isRed;
}

int CTRAFFICLIGHT::calcTFLightYCoord(int lane) {
	return lane - fieldConstraints::VER_SPEED + TFLIGHT_HEIGHT;
}

void CTRAFFICLIGHT::eraseTFLightAndFixBoard(int vehicle) {
	CCONSOLE::eraseGraphics({ x, y }, { x + TFLIGHT_WIDTH, y + TFLIGHT_HEIGHT });

	switch (vehicle) {
	case vehicles::CAR:
		for (int i = 0; i <= 1; i++) CCONSOLE::drawTexts("|", { x + TFLIGHT_WIDTH / 2, y + i }, FIELD_COLOR);
		break;
	case vehicles::BUS:
		for (int i = 0; i <= 1; i++) CCONSOLE::drawTexts("|", { x, y + i }, FIELD_COLOR);
	}
}

template<class Obj>
void CTRAFFICLIGHT::updateLightStatus(vector<Obj*>& objVect, int lane) {
	timeElapsed++;

	if (isRed && timeElapsed >= redTime) isRed = false, timeElapsed = 0;
	else if (!isRed && timeElapsed >= greenTime) isRed = true, timeElapsed = 0;

	updateSprite(lane);
	for (auto obj : objVect) obj->setRedLight(isRed);
}

/* Read Chapter 6, page 61 to 63 for explanation on why the these two lines of code are necessary. 
 * -> https://books.google.com.vn/books?id=EotSAwuBkJoC&pg=PA61&lpg=PA61&dq=Inclusion+model+in+templates&source=bl&ots=iwO-H5_f8b&sig=_lQy9I36pfxWuU5iIw1IDCw-uK0&hl=en&ei=guCOTMbqGJHyvQPzs9DUCw&sa=X&oi=book_result&ct=result&redir_esc=y#v=onepage&q=Inclusion%20model%20in%20templates&f=false
*/
template void CTRAFFICLIGHT::updateLightStatus<CCAR>(vector<CCAR*>&, int);
template void CTRAFFICLIGHT::updateLightStatus<CBUS>(vector<CBUS*>&, int);