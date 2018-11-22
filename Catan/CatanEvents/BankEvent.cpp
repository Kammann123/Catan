#include "BankEvent.h"

BankEvent::
BankEvent(BankPacket* packet) : CatanEvent(Events::BANK_TRADE, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->givenResource = packet->getGivenResource();
	this->receivedResource = packet->getReceivedResource();
}

BankEvent::
BankEvent(list<ResourceId> given, list<ResourceId> recv) : CatanEvent(Events::BANK_TRADE, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->givenResource = given;
	this->receiveResource = recv;
}

BankEvent::
~BankEvent() {}

list<ResourceId>& 
BankEvent::getGivenResources(void) {
	return this->givenResource;
}

list<ResourceId>&
BankEvent::getReceivedResources(void) {
	return this->receivedResource;
}