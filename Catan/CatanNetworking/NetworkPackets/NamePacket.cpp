#include "NamePacket.h"

NamePacket::
NamePacket(void) : NetworkPacket(PacketHeader::NAME_IS) {

	name.clear();
}

NamePacket::
~NamePacket(void) {}

void
NamePacket::setName(string& name) {

	this->name = name;
}

void
NamePacket::setName(char letter) {

	this->name += letter;
}

string&
NamePacket::getName(void) {

	return this->name;
}

unsigned char*
NamePacket::getDataStream(unsigned int& length) {

	/* Calculo longitud del buffer */
	unsigned int bufferLength = 2 + name.size();

	/* Crear el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo y guardo */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = name.size();
	unsigned int i = 2;
	for (unsigned char c : name) {
		buff[i++] = c;
	}

	/* Devuelvo */
	return buff;
}