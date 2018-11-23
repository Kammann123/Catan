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
	unsigned int i = 1;
	for (DevCardId card : this->getCards()) {
		buff[i++] = (unsigned char)card;
	}

	/* Devuelvo */
	return buff;
}