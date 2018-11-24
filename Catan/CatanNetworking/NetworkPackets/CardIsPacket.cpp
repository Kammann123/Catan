#include "CardIsPacket.h"

CardIsPacket::
CardIsPacket(CardIsData data) : NetworkPacket(PacketHeader::CARD_IS), CardIsData(data) {}

CardIsPacket::
CardIsPacket() : NetworkPacket(PacketHeader::CARD_IS), CardIsData() {}

CardIsPacket::
CardIsPacket(ResourceId res) : NetworkPacket(PacketHeader::CARD_IS), CardIsData(res) {}

CardIsPacket::
~CardIsPacket() {}

unsigned char* 
CardIsPacket::getDataStream(unsigned int& length) {

	unsigned int bufferLength = 2;

	length = bufferLength;

	unsigned char * buff = new unsigned char[bufferLength];

	buff[0] = this->getHeader();
	buff[1] = (unsigned char)this->getResource();

	return buff;
}