#include "NamePacket.h"

NamePacket::
NamePacket(void) : NetworkPacket(PacketHeader::NAME_IS), NameData() {}

NamePacket::
NamePacket(string name) : NetworkPacket(PacketHeader::NAME_IS), NameData(name) {}

NamePacket::
~NamePacket(void) {}

unsigned char*
NamePacket::getDataStream(unsigned int& length) {

	string name = this->getName();

	/* Calculo longitud del buffer */
	unsigned int bufferLength = 2 + name.size();

	/* Crear el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo y guardo */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = name.size();
	unsigned int i = 2;
	for (unsigned char c : name) {
		buff[i++] = c;
	}

	/* Devuelvo */
	return buff;
}