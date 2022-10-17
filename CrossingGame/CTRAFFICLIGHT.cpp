#pragma once
#include "CTRAFFICLIGHT.h"

CTRAFFICLIGHT::CTRAFFICLIGHT(int greenTime, int redTime) {
	this->isRed = false;
	this->greenTime = greenTime;
	this->redTime = redTime;
	this->timeElapsed = 0;
}

void CTRAFFICLIGHT::updateSprite(int& lane) {
	if (isRed) {
		switch (lane) {
		case vehicles::CAR:
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, TFLIGHT_CAR_LANE_COORD, colors::BLACK);
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { TFLIGHT_CAR_LANE_COORD.x, TFLIGHT_CAR_LANE_COORD.y + 1 }, colors::RED);
			break;
		case vehicles::BUS:
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, TFLIGHT_BUS_LANE_COORD, colors::BLACK);
			CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { TFLIGHT_BUS_LANE_COORD.x, TFLIGHT_CAR_LANE_COORD.y + 1 }, colors::RED);
		}

		return;
	}

	switch (lane) {
	case vehicles::CAR:
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, TFLIGHT_CAR_LANE_COORD, colors::GREEN);
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { TFLIGHT_CAR_LANE_COORD.x, TFLIGHT_CAR_LANE_COORD.y + 1 }, colors::BLACK);
		break;
	case vehicles::BUS:
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, TFLIGHT_BUS_LANE_COORD, colors::GREEN);
		CCONSOLE::drawGraphics(TFLIGHT_SPRITE, { TFLIGHT_BUS_LANE_COORD.x, TFLIGHT_BUS_LANE_COORD.y + 1 }, colors::BLACK);
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

/* Read Chapter 6, page 61 to 63 for explanation on why the these two lines of code
 * are necessary. 
 * -> https://books.google.com.vn/books?id=EotSAwuBkJoC&pg=PA61&lpg=PA61&dq=Inclusion+model+in+templates&source=bl&ots=iwO-H5_f8b&sig=_lQy9I36pfxWuU5iIw1IDCw-uK0&hl=en&ei=guCOTMbqGJHyvQPzs9DUCw&sa=X&oi=book_result&ct=result&redir_esc=y#v=onepage&q=Inclusion%20model%20in%20templates&f=false
*/
template void CTRAFFICLIGHT::updateLightStatus<CCAR>(vector<CCAR*>&, int);
template void CTRAFFICLIGHT::updateLightStatus<CBUS>(vector<CBUS*>&, int);