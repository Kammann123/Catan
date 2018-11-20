#include "TokenPacket.h"

TokenPacket::
TokenPacket(void) : NetworkPacket(PacketHeader::CIRCULAR_TOKENS) {
	this->tokens.clear();
}

TokenPacket::
~TokenPacket() {}

bool
TokenPacket::setToken(unsigned char cell, unsigned char token) {

	/* Valido posicion */
	if ( isMapPosition(cell) ) {

		/* Valido valor de token */
		if ( isValidToken(token) ) {

			this->tokens[cell] = token;
			return true;
		}
	}
	return false;
}

map<unsigned char, unsigned char>& 
TokenPacket::getTokens(void) {

	return this->tokens;
}

unsigned char*
TokenPacket::getDataStream(unsigned int& length) {

	/* Longitud del buffer */
	unsigned int bufferLength = 1 + tokens.size();

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Armo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	unsigned int ii = 1;
	for (unsigned char i = 'A'; i <= 'S'; i++) {
		if (tokens.find(i) != tokens.end()) {
			buff[ii++] = tokens[i];
		}
	}

	/* Devuelvo */
	return buff;
}