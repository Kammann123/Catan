#include "NetworkPacket.h"

/* NetworkPacket Metodos Definiciones */

NetworkPacket::
NetworkPacket(PacketHeader header) {

	this->header = header;
}

NetworkPacket::
~NetworkPacket() {}

PacketHeader
NetworkPacket::getHeader(void) const {

	return this->header;
}

unsigned char*
NetworkPacket::getDataStream(unsigned int& length) {

	/* Armo el mensaje o paquete */
	unsigned char* buff = new unsigned char[1];

	/* Guardo el dato */
	buff[0] = (unsigned char)this->header;
	length = 1;

	return buff;
}