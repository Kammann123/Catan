#include "MonopolyPacket.h"

MonopolyPacket::
MonopolyPacket(void) : NetworkPacket(PacketHeader::MONOPOLY) {}

MonopolyPacket::
~MonopolyPacket(void) {}

ResourceId
MonopolyPacket::getResource(void) {
	return this->resource;
}

void
MonopolyPacket::setResource(ResourceId resource) {
	this->resource = resource;
}

unsigned char* 
MonopolyPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 2;

	unsigned char* buff = new unsigned char[bufferLength];

	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = (unsigned char)this->resource;

	return buff;
}