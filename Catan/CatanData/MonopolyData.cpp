#include "MonopolyData.h"

MonopolyData::
MonopolyData(ResourceId res) : CatanData(CatanData::Type::MONOPOLY) {
	this->res = res;
}

MonopolyData::
MonopolyData() : CatanData(CatanData::Type::MONOPOLY){}

void
MonopolyData::setResource(ResourceId res) {
	this->res = res;
}

ResourceId 
MonopolyData::getResource(void) {
	return this->res;
}