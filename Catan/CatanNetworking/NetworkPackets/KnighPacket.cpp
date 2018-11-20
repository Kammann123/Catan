#include "KnightPacket.h"

KnightPacket::
KnightPacket(void) : NetworkPacket(PacketHeader::KNIGHT) {}

KnightPacket::
~KnightPacket(void) {}

bool
KnightPacket::setCoord(unsigned char coord) {
	if (isMapPosition(coord)) {
		this->coord = coord;
		return true;
	}
	else {
		return false,
	}
}

unsigned char 
KnightPacket::getCoord(void) {
	return this->coord;
}

unsigned char*
KnightPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 2;

	unsigned char* buff = new unsigned char[bufferLength];
	
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = (unsigned char)this->coord;

	return buff;
}