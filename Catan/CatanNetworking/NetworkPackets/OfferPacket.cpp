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

unsigned char*
OfferPacket::getDataStream(unsigned int& length) {

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 3 + givenResources.size() + receivedResources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];
	
	/* Armo y guardo paquete */
	buff[0] = (unsigned char)this->header;
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