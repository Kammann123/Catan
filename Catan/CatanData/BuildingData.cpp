#include "BuildingData.h"

BuildingData::
BuildingData(BuildingType type, Coord coords) : CatanData(CatanData::Type::BUILDING) {
	this->type = type;
	this->coords = coords;
}

BuildingData::
BuildingData() : CatanData(CatanData::Type::BUILDING) {
	this->coords = "";
}

bool 
BuildingData::setCoords(Coord coord) {
	if (coord.isLand() || coord.isSea()) {
		this->coords += coord;
		return true;
	}
	return false;
}

void
BuildingData::setType(BuildingType type) {
	this->type = type;
}

Coord&
BuildingData::getCoords(void) {
	return this->coords;
}

BuildingType 
BuildingData::getType(void) {
	return this->type;
}