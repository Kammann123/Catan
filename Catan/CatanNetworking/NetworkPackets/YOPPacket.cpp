#include "YOPPacket.h"

YOPPacket::
YOPPacket(ResourceId fRes, ResourceId sRes) : NetworkPacket(PacketHeader::YEARS_OF_PLENTY), YOPData(fRes, sRes) {}

YOPPacket::
YOPPacket(YOPData data) : NetworkPacket(PacketHeader::YEARS_OF_PLENTY), YOPData(data) {}

YOPPacket::
YOPPacket(void) : NetworkPacket(PacketHeader::YEARS_OF_PLENTY), YOPData() {}

YOPPacket::
~YOPPacket() {}

unsigned char*
YOPPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 3;

	unsigned char* buff = new unsigned char[bufferLength];

	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)this->getFirstResource();
	buff[2] = (unsigned char)this->getSecondResource();

	return buff;
}