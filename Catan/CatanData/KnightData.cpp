#include "KnightData.h"

KnightData::
KnightData(unsigned char coord) : CatanData(CatanData::Type::KNIGHT) {
	this->coord = coord;
}

KnightData::
KnightData() : CatanData(CatanData::Type::KNIGHT){}

bool
KnightData::setCoord(unsigned char c) {
	if (isMapPosition(c)) {
		this->coord = c;
		return true;
	}
	return false;
}

unsigned char
KnightData::getCoord(void) {
	return this->coord;
}