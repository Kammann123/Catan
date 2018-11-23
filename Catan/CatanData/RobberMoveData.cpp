#include "RobberMoveData.h"

RobberMoveData::
RobberMoveData(unsigned char c) : CatanData(CatanData::Type::ROBBER_MOVE) {
	this->coord = c;
}

RobberMoveData::
RobberMoveData() : CatanData(CatanData::Type::ROBBER_MOVE) {}

bool
RobberMoveData::setCoord(unsigned char c) {
	if (isMapPosition(c)) {
		this->coord = c;
		return true;
	}
	return false;
}

unsigned char
RobberMoveData::getCoord(void) {
	return this->coord;
}