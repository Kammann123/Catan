#include "MapData.h"

MapData::
MapData(map<unsigned char, MapValue> m) : CatanData(CatanData::Type::MAP) {
	this->gameMap = m;
}

MapData::
MapData() : CatanData(CatanData::Type::MAP) {}

bool
MapData::setMap(unsigned char coord, MapValue value) {
	if (isMapPosition(coord) || isSeaPosition(coord)) {
		this->gameMap[coord] = value;
		return true;
	}

	return false;
}

map<unsigned char, MapValue>&
MapData::getMap(void) {
	return gameMap;
}