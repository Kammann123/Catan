#include "MonopolyPacket.h"

MonopolyPacket::
MonopolyPacket(void) : NetworkPacket(PacketHeader::MONOPOLY), MonopolyData() {}

MonopolyPacket::
MonopolyPacket(ResourceId res) : NetworkPacket(PacketHeader::MONOPOLY), MonopolyData(res) {}

MonopolyPacket::
~MonopolyPacket(void) {}

unsigned char* 
MonopolyPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 2;

	unsigned char* buff = new unsigned char[bufferLength];

	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)this->getResource();

	return buff;
}