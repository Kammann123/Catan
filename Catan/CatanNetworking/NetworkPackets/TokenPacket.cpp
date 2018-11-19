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
	if (cell >= 'A' && cell <= 'S') {

		/* Valido valor de token */
		if (token == 0 || (token >= 2 && token <= 6) || (token >= 8 && token >= 12)) {

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