#include "CityPacket.h"

CityPacket::
CityPacket() : NetworkPacket(PacketHeader::CITY) {}

CityPacket::
~CityPacket() {}

bool 
CityPacket::setCoord(unsigned char coord, unsigned char indexCoord) {

	/* Valido posicion e indice */
	if (indexCoord < 3) {

		/* Guardo coordenada */
		this->coord[indexCoord] = coord;
		return true;
	}
	else {
		return false;
	}
}

unsigned char
CityPacket::getCoord(unsigned char indexCoord) {

	/* Valido posicion */
	if (indexCoord < 3) {
		return this->coord[indexCoord];
	}
	else {
		return 0xFF;
	}
}