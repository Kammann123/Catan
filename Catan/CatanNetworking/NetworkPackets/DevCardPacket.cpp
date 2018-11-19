#include "DevCardPacket.h"

DevCardPacket::
DevCardPacket(void) : NetworkPacket(PacketHeader::DEV_CARDS) {}

DevCardPacket::
~DevCardPacket(void) {}

bool 
DevCardPacket::setCard(DevCardId card, unsigned char indexCard) {

	/* Verifico posicion */
	if (indexCard < 25) {
		this->cards[indexCard] = card;
		return true;
	}
	else {
		return false;
	}
}

bool
DevCardPacket::getCard(DevCardId& card, unsigned char indexCard) {

	/* Verifico posicion */
	if (indexCard < 25) {
		card = this->cards[indexCard];
		return true;
	}
	else {
		return false;
	}
}

unsigned char*
DevCardPacket::getDataStream(unsigned int& length) {

	/* Calculo el largo del buffer */
	unsigned int bufferLength = 26;

	/* Creo el buffer */
	unsigned char* buff = new unsigned char[bufferLength];

	/* Guardo y creo el paquete */
	length = bufferLength;
	buff[0] = (unsigned char)this->header;
	for (unsigned int i = 1; i <= 26; i++) {
		buff[i] = (unsigned char)cards[i - 1];
	}

	/* Devuelvo */
	return buff;
}