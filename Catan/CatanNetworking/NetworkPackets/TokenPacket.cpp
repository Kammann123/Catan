#include "TokenPacket.h"

TokenPacket::
TokenPacket(map<unsigned char, unsigned char> tokens) : NetworkPacket(PacketHeader::CIRCULAR_TOKENS), TokenData(tokens) {}

TokenPacket::
TokenPacket(TokenData data) : NetworkPacket(PacketHeader::CIRCULAR_TOKENS), TokenData(data) {}

TokenPacket::
TokenPacket(void) : NetworkPacket(PacketHeader::CIRCULAR_TOKENS), TokenData() {}

TokenPacket::
~TokenPacket() {}

unsigned char*
TokenPacket::getDataStream(unsigned int& length) {

	map<unsigned char, unsigned char> tokens = this->getTokens();

	/* Longitud del buffer */
	unsigned int bufferLength = 1 + (unsigned int)tokens.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->getHeader();
	unsigned int ii = 1;
	for (unsigned char i = 'A'; i <= 'S'; i++) {
		if (tokens.find(i) != tokens.end()) {
			buff[ii++] = tokens[i];
		}
	}

	/* Devuelvo */
	return buff;
}