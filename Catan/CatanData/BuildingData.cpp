#include "BuildingData.h"

BuildingData::
BuildingData(BuildingType type, string coords) : CatanData(CatanData::Type::BUILDING) {
	this->type = type;
	this->coords = coords;
}

BuildingData::
BuildingData() : CatanData(CatanData::Type::BUILDING) {
	this->coords = "";
}

bool
BuildingData::setCoords(string coords){

	/* Valido todas coordenadas */
	for (unsigned char c : coords) {
		if (!isMapPosition(c) && !isSeaPosition(c)) {
			return false;
		}
	}

	/* Ok! */
	this->coords = coords;
	return true;
}

bool 
BuildingData::setCoords(unsigned char coord) {
	if (isMapPosition(c) || isSeaPosition(c)) {
		this->coords += coord;
		return true;
	}
	return false;
}

void
BuildingData::setType(BuildingType type) {
	this->type = type;
}

string
BuildingData::getCoords(void) {
	return this->coords;
}

BuildingType 
BuildingData::getType(void) {
	return this->type;
}