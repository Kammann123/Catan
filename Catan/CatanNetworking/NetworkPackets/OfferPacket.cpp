#include "OfferPacket.h"

OfferPacket::
OfferPacket(void) : NetworkPacket(PacketHeader::OFFER_TRADE) {
	this->givenResources.clear();
	this->receivedResources.clear();
}

OfferPacket::
~OfferPacket() {}

void
OfferPacket::addGivenResource(ResourceId resource) {
	this->givenResources.push_back(resource);
}

void
OfferPacket::addReceivedResource(ResourceId resource) {
	this->receivedResources.push_back(resource);
}

list<ResourceId>&
OfferPacket::getGivenResources(void) {
	return this->givenResources;
}

list<ResourceId>&
OfferPacket::getReceivedResources(void) {
	return this->receivedResources;
}