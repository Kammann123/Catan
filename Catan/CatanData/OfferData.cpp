#include "OfferData.h"

OfferData::
OfferData(list<ResourceId> given, list<ResourceId> recv) : CatanData(CatanData::Type::OFFER) {
	this->given = given;
	this->recv = recv;
}

OfferData::
OfferData(list<ResourceCard*> given, list<ResourceId> recv) : CatanData(CatanData::Type::OFFER) {
	this->givenCards = given;
	this->recv = recv;
}

OfferData::
OfferData() : CatanData(CatanData::Type::OFFER) {}

void
OfferData::setGiven(ResourceId res) {
	this->given.push_back(res);
}

void
OfferData::setRecv(ResourceId res) {
	this->recv.push_back(res);
}

list<ResourceId>&
OfferData::getGiven(void) {
	return given;
}

list<ResourceId>&
OfferData::getRecv(void) {
	return recv;
}

void
OfferData::setGivenCard(ResourceCard* res) {
	givenCards.push_back(res);
}

list<ResourceCard*>& 
OfferData::getGivenCards(void) {
	return givenCards;
}

bool
OfferData::hasLocal(void) {
	return (givenCards.size() > 0);
}

bool
OfferData::hasRemote(void) {
	return (given.size() > 0);
}