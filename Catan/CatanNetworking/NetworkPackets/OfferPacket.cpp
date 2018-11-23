#include "OfferPacket.h"

OfferPacket::
OfferPacket(void) : NetworkPacket(PacketHeader::OFFER_TRADE), OfferData() {}

OfferPacket::
OfferPacket(list<ResourceId> given, list<ResourceId> recv) : NetworkPacket(PacketHeader::OFFER_TRADE), OfferData(given, recv) {}

OfferPacket::
~OfferPacket() {}

unsigned char*
OfferPacket::getDataStream(unsigned int& length) {

	list<ResourceId> givenResources = this->getGiven();
	list<ResourceId> receivedResources = this->getRecv();

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 3 + givenResources.size() + receivedResources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];
	
	/* Armo y guardo paquete */
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = givenResources.size();
	buff[2] = receivedResources.size();
	unsigned int i = 3;
	for (ResourceId r : givenResources) {
		buff[i++] = (unsigned char)r;
	}
	for (ResourceId r : receivedResources) {
		buff[i++] = (unsigned char)r;
	}

	/* Devuelvo */
	return buff;
}