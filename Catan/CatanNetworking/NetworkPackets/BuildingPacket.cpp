#include "BuildingPacket.h"

BuildingPacket::
BuildingPacket(PacketHeader header) : NetworkPacket(header) {

	coords.clear();
}

BuildingPacket::
~BuildingPacket() {}

void
BuildingPacket::setCoords(unsigned char coord) {

	coords += coord;
}

void
BuildingPacket::setCoords(string& coords) {

	this->coords = coords;
}

string&
BuildingPacket::getCoords(void) {

	return this->coords;
}

unsigned char*
BuildingPacket::getDataStream(unsigned int& length) {

	/* Calculo la cantidad */
	unsigned int bufferLength = 2 + coords.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = coords.size();
	unsigned int i = 2;
	for (unsigned char c : coords) {
		buff[i++] = c;
	}

	/* Devuelvo */
	return buff;
}