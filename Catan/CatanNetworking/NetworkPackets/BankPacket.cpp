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

unsigned char*
BankPacket::getDataStream(unsigned int& length) {

	/* Calculo el largo necesario */
	unsigned int bufferLength = 2 + givenResources.size() + receivedResources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo la informacion y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = givenResources.size();
	unsigned int i = 2;
	for (ResourceId r : givenResources) {
		buff[i++] = (unsigned char)r;
	}
	for (ResourceId r : receivedResources) {
		buff[i++] = (unsigned char)r;
	}

	/* Devuelvo el resultado */
	return buff;
}