#include "RobberCardPacket.h"

RobberCardPacket::
RobberCardPacket(void) : NetworkPacket(PacketHeader::ROBBER_CARDS), RobberCardData() {}

RobberCardPacket::
RobberCardPacket(list<ResourceId> resources) : NetworkPacket(PacketHeader::ROBBER_CARDS), RobberCardData(resources) {}

RobberCardPacket::
~RobberCardPacket() {}

unsigned char*
RobberCardPacket::getDataStream(unsigned int& length) {

	list<ResourceId> resources = this->getResources();

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 2 + resources.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete y guardo */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)resources.size();
	unsigned int i = 2;
	for (ResourceId r : resources) {

		buff[i++] = (unsigned char)r;
	}

	/* Devuelvo */
	return buff;
}