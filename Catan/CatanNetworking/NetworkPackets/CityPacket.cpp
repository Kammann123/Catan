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
		if ((coord >= '0' && coord <= '6') || (coord >= 'A' && coord <= 'S')) {
			this->coord[indexCoord] = coord;
			return true;
		}
	}
	return false;
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