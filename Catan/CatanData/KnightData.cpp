#include "KnightData.h"

KnightData::
KnightData(Coord coord) : CatanData(CatanData::Type::KNIGHT) {
	this->coord = coord;
}

KnightData::
KnightData() : CatanData(CatanData::Type::KNIGHT){}

bool
KnightData::setCoord(Coord c) {
	if ( c.isLand() ) {
		this->coord = c;
		return true;
	}
	return false;
}

Coord
KnightData::getCoord(void) {
	return this->coord;
}