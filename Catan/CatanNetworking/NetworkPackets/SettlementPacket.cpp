#include "SettlementPacket.h"

SettlementPacket::
SettlementPacket(void) : NetworkPacket(PacketHeader::SETTLEMENT) {}

SettlementPacket::
~SettlementPacket(void) {}

bool 
SettlementPacket::setCoord(unsigned char coord, unsigned char indexCoord) {

	/* Valido la posicion */
	if (indexCoord < 3) {
		
		/* Valido valor o contenido */
		if ((coord >= '0' && coord <= '6') || (coord >= 'A' && coord <= 'S')) {
			this->coord[indexCoord] = coord;
			return true;
		}
	}
	return false;
}

unsigned char
SettlementPacket::getCoord(unsigned char indexCoord) {
	
	/* Valido la posicion */
	if (indexCoord < 3) {

		return this->coord[indexCoord];
	}
	return 0xFF;
}