#include "RobberMovePacket.h"

RobberMovePacket::
RobberMovePacket(void) : NetworkPacket(PacketHeader::ROBBER_MOVE) {}

RobberMovePacket::
~RobberMovePacket() {}

bool 
RobberMovePacket::setCoord(unsigned char coord) {

	/* Verifico posicion */
	if (coord >= 'A' && coord >= 'B') {
		this->coord = coord;
		return true;
	}
	return false;
}

unsigned char
RobberMovePacket::getCoord(void) {

	return this->coord;
}