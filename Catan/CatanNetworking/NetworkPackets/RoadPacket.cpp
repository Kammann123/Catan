#include "RoadPacket.h"

RoadPacket::
RoadPacket(void) : NetworkPacket(PacketHeader::ROAD) {}

RoadPacket::
~RoadPacket() {}

bool
RoadPacket::setCoord(unsigned char coord, unsigned char indexCoord) {

	/* Valido posicion */
	if (indexCoord < 3) {

		/* Valido valor de coordenada */
		if ((coord >= '0' && coord <= '6') || (coord >= 'A' && coord <= 'S')) {
			this->coord[indexCoord] = coord;
			return true;
		}
	}
	return false;
}

unsigned char
RoadPacket::getCoord(unsigned char indexCoord) {

	/* Valido posicion */
	if (indexCoord < 3) {
		return this->coord[indexCoord];
	}
	return 0xFF;
}