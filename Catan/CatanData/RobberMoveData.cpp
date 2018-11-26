#include "RobberMoveData.h"

RobberMoveData::
RobberMoveData(Coord c) : CatanData(CatanData::Type::ROBBER_MOVE) {
	this->coord = c;
}

RobberMoveData::
RobberMoveData() : CatanData(CatanData::Type::ROBBER_MOVE) {}

bool
RobberMoveData::setCoord(Coord c) {
	if (c.isLand()) {
		this->coord = c;
		return true;
	}
	return false;
}

Coord
RobberMoveData::getCoord(void) {
	return this->coord;
}