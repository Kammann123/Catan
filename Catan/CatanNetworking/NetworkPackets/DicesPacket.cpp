#include "DicesPacket.h"

DicesPacket::
DicesPacket(void) : NetworkPacket(PacketHeader::DICES_ARE) {}

DicesPacket::
~DicesPacket() {}

bool
DicesPacket::_set_dice(unsigned char dice, Dices diceIndex) {

	/* Verifico valor */
	if( dice <= 6 ){
		dices[(unsigned int)diceIndex] = dice;
		return true;
	}
	else {
		return false;
	}
}

bool
DicesPacket::setFirstDice(unsigned char dice) {

	return _set_dice(dice, DicesPacket::Dices::FIRST);
}

bool
DicesPacket::setSecondDice(unsigned char dice) {

	return _set_dice(dice, DicesPacket::Dices::SECOND);
}

unsigned char
DicesPacket::getFirstDice(void) {

	return dices[(unsigned int)DicesPacket::Dices::FIRST];
}

unsigned char
DicesPacket::getSecondDice(void) {

	return dices[(unsigned int)DicesPacket::Dices::SECOND];
}