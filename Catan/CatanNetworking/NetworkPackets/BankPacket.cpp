#include "BankPacket.h"

BankPacket::
BankPacket(BankData data) : NetworkPacket(PacketHeader::BANK_TRADE), BankData(data) {}

BankPacket::
BankPacket(void) : NetworkPacket(PacketHeader::BANK_TRADE), BankData() {}

BankPacket::
BankPacket(list<ResourceId> given, list<ResourceId> recv) : NetworkPacket(PacketHeader::BANK_TRADE), BankData(given, recv) {}

BankPacket::
~BankPacket() {}

unsigned char*
BankPacket::getDataStream(unsigned int& length) {

	list<ResourceId> givenResources = this->getGiven();
	list<ResourceId> receivedResources = this->getRecv();

	/* Calculo el largo necesario */
	unsigned int bufferLength = 2 + givenResources.size() + receivedResources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo la informacion y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)givenResources.size();
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