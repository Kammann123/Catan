#include "RobberCardData.h"

RobberCardData::
RobberCardData(list<ResourceId> resources) : CatanData(CatanData::Type::ROBBER_CARDS) {
	this->resources = resources;
}

RobberCardData::
RobberCardData() : CatanData(CatanData::Type::ROBBER_CARDS) {}

void
RobberCardData::setResource(ResourceId res) {
	resources.push_back(res);
}

list<ResourceId>& 
RobberCardData::getResources(void) {
	return this->resources;
}