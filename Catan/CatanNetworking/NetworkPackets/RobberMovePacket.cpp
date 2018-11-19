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

unsigned char*
RobberMovePacket::getDataStream(unsigned int& length) {

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 2;

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = coord;

	/* Devuelvo */
	return buff;
}