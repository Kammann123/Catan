#include "DicesEvent.h"

DicesEvent::
DicesEvent(DicesPacket* packet) : CatanEvent(Events::THROW_DICES, Sources::NETWORKING, PlayerId::PLAYER_TWO){
	this->dices = packet->getFirstDice() + packet->getSecondDice();
}

DicesEvent::
DicesEvent(unsigned int firstDice, unsigned int secondDice) : CatanEvent(Events::THROW_DICES, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->dices = firstDice + secondDice;
}

DicesEvent::
DicesEvent(unsigned int dices) : CatanEvent(Events::THROW_DICES, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->dices = dices;
}

DicesEvent::
~DicesEvent(void) {}

unsigned int 
DicesEvent::getDices(void) const {
	return this->dices;
}