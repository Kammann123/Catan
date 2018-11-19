#include "RobberCardPacket.h"

RobberCardPacket::
RobberCardPacket(void) : NetworkPacket(PacketHeader::ROBBER_CARDS) {
	this->resources.clear();
}

RobberCardPacket::
~RobberCardPacket() {}

void
RobberCardPacket::addResource(ResourceId resource) {
	this->resources.push_back(resource);
}

list<ResourceId>&
RobberCardPacket::getResources(void) {
	return this->resources;
}

unsigned char*
RobberCardPacket::getDataStream(unsigned int& length) {

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 2 + resources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete y guardo */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = resources.size();
	unsigned int i = 2;
	for (ResourceId r : resources) {

		buff[i++] = (unsigned char)r;
	}

	/* Devuelvo */
	return buff;
}