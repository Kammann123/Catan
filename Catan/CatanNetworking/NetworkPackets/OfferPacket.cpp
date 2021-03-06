#include "OfferPacket.h"

OfferPacket::
OfferPacket(OfferData data) : NetworkPacket(PacketHeader::OFFER_TRADE), OfferData(data) {}

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
	unsigned int bufferLength = 3 + (unsigned int)givenResources.size() + (unsigned int)receivedResources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];
	
	/* Armo y guardo paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)givenResources.size();
	buff[2] = (unsigned char)receivedResources.size();
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