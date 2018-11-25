#include "NamePacket.h"

NamePacket::
NamePacket(void) : NetworkPacket(PacketHeader::NAME_IS), NameData() {}

NamePacket::
NamePacket(NameData data) : NetworkPacket(PacketHeader::NAME_IS), NameData(data) {}

NamePacket::
NamePacket(string name) : NetworkPacket(PacketHeader::NAME_IS), NameData(name) {}

NamePacket::
~NamePacket(void) {}

string
NamePacket::getString(void) {
	string name = this->getName();
	string msg = string("[NamePacket] ") + string(HeaderStrings[getHeader()]) + " " + name;
	return msg;
}

unsigned char*
NamePacket::getDataStream(unsigned int& length) {

	string name = this->getName();

	/* Calculo longitud del buffer */
	unsigned int bufferLength = 2 + (unsigned int)name.size();

	/* Crear el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo y guardo */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)name.size();
	unsigned int i = 2;
	for (unsigned char c : name) {
		buff[i++] = c;
	}

	/* Devuelvo */
	return buff;
}