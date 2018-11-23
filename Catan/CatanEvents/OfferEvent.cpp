#include "OfferEvent.h"

OfferEvent::
OfferEvent(OfferPacket* packet) : CatanEvent(Events::OFFER_TRADE, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->given = packet->getGivenResources();
	this->recv = packet->getReceivedResources();
}

OfferEvent::
OfferEvent(list<ResourceId> given, list<ResourceId> recv, PlayerId player) : CatanEvent(Events::OFFER_TRADE, Sources::GUI, player) {
	this->given = given;
	this->recv = recv;
}

OfferEvent::
~OfferEvent() {}

list<ResourceId>&
OfferEvent::getGiven(void) {
	return this->given;
}

list<ResourceId>&
OfferEvent::getRecv(void) {
	return this->recv;
}