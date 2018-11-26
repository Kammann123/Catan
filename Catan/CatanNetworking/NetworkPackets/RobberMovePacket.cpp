#include "RobberMovePacket.h"

RobberMovePacket::
RobberMovePacket(Coord coord) : NetworkPacket(PacketHeader::ROBBER_MOVE), RobberMoveData(coord) {}

RobberMovePacket::
RobberMovePacket(RobberMoveData data) : NetworkPacket(PacketHeader::ROBBER_MOVE), RobberMoveData(data) {}

RobberMovePacket::
RobberMovePacket(void) : NetworkPacket(PacketHeader::ROBBER_MOVE), RobberMoveData() {}

RobberMovePacket::
~RobberMovePacket() {}

unsigned char*
RobberMovePacket::getDataStream(unsigned int& length) {

	/* Calculo la longitud del buffer */
	unsigned int bufferLength = 2;

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	buff[1] = (unsigned char)this->getCoord().getCoords()[0];

	/* Devuelvo */
	return buff;
}