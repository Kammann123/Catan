#include "OfferData.h"

OfferData::
OfferData(list<ResourceId> given, list<ResourceId> recv) : CatanData(CatanData::Type::OFFER) {
	this->given = given;
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