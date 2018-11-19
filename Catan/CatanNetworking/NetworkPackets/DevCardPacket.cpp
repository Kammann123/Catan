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