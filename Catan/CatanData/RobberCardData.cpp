#include "RobberCardData.h"

RobberCardData::
RobberCardData(list<ResourceId> resources) : CatanData(CatanData::Type::ROBBER_CARDS) {
	this->resources = resources;
}

RobberCardData::
RobberCardData(list<ResourceCard*> resources) : CatanData(CatanData::Type::ROBBER_CARDS) {
	this->cards = resources;
}

RobberCardData::
RobberCardData() : CatanData(CatanData::Type::ROBBER_CARDS) {}

void
RobberCardData::setResource(ResourceId res) {
	resources.push_back(res);
}

void
RobberCardData::setResource(ResourceCard* res) {
	cards.push_back(res);
}

list<ResourceId>& 
RobberCardData::getResources(void) {
	return this->resources;
}

list<ResourceCard*>&
RobberCardData::getResourceCards(void) {
	return this->cards;
}

bool
RobberCardData::hasLocal(void) {
	return (this->cards.size() > 0);
}

bool
RobberCardData::hasRemote(void) {
	return (this->resources.size() > 0);
}