#include "MapData.h"

MapData::
MapData(map<Coord, MapValue> m) : CatanData(CatanData::Type::MAP) {
	this->gameMap = m;
}

MapData::
MapData() : CatanData(CatanData::Type::MAP) {}

bool
MapData::setMap(Coord coord, MapValue value) {
	if (coord.isLand() || coord.isSea()) {
		this->gameMap[coord] = value;
		return true;
	}

	return false;
}

map<Coord, MapValue>&
MapData::getMap(void) {
	return gameMap;
}