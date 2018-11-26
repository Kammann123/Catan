#include "KnightPacket.h"

KnightPacket::
KnightPacket(KnightData data) : NetworkPacket(PacketHeader::KNIGHT), KnightData(data) {}

KnightPacket::
KnightPacket(void) : NetworkPacket(PacketHeader::KNIGHT), KnightData() {}

KnightPacket::
KnightPacket(Coord coord) : NetworkPacket(PacketHeader::KNIGHT), KnightData(coord) {}

KnightPacket::
~KnightPacket(void) {}

unsigned char*
KnightPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 2;

	unsigned char* buff = new unsigned char[bufferLength];
	
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)this->getCoord().getCoords()[0];

	return buff;
}