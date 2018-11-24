#include "DicesPacket.h"

DicesPacket::
DicesPacket(DicesData data) : NetworkPacket(PacketHeader::DICES_ARE), DicesData(data) {}

DicesPacket::
DicesPacket(void) : NetworkPacket(PacketHeader::DICES_ARE), DicesData() {}

DicesPacket::
DicesPacket(unsigned int fDice, unsigned int sDice) : NetworkPacket(PacketHeader::DICES_ARE), DicesData(fDice, sDice) {}

DicesPacket::
~DicesPacket() {}

unsigned char*
DicesPacket::getDataStream(unsigned int& length) {

	/* Calculo el largo del buffer */
	unsigned int bufferLength = 3;

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	buff[1] = this->getFirstDice();
	buff[2] = this->getSecondDice();
	
	/* Devuelvo */
	return buff;
}