#include "DevCardPacket.h"

DevCardPacket::
DevCardPacket(void) : NetworkPacket(PacketHeader::DEV_CARDS), DevCardsData() {}

DevCardPacket::
DevCardPacket(list<DevCardId> cards) : NetworkPacket(PacketHeader::DEV_CARDS), DevCardsData(cards) {}

DevCardPacket::
~DevCardPacket(void) {}

unsigned char*
DevCardPacket::getDataStream(unsigned int& length) {

	list<DevCardId> cards = this->getCards();

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