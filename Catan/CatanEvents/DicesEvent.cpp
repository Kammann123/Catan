#include "DicesEvent.h"

DicesEvent::
DicesEvent(unsigned int firstDice, unsigned int secondDice) : CatanEvent(CatanEvent::Events::THROW_DICES) {
	this->dices = firstDice + secondDice;
}

DicesEvent::
DicesEvent(unsigned int dices) : CatanEvent(CatanEvent::Events::THROW_DICES) {
	this->dices = dices;
}

~DicesEvent(void) {}

unsigned int getDices(void) const {
	return this->dices;
}