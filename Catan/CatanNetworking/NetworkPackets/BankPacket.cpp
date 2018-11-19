#include "BankPacket.h"

BankPacket::
BankPacket(void) : NetworkPacket(PacketHeader::BANK_TRADE) {
	/* Inicializo */
	this->givenResources.clear();
	this->receivedResources.clear();
}

BankPacket::
~BankPacket() {}

void BankPacket::
addGivenResources(ResourceId resource) {

	this->givenResources.push_back(resource);
}
void BankPacket::
addReceivedResources(ResourceId resource) {

	this->receivedResources.push_back(resource);
}

list<ResourceId>& BankPacket::
getGivenResources(void) {

	return this->givenResources;
}

list<ResourceId>& BankPacket::
getReceivedResources(void) {

	return this->receivedResources;
}