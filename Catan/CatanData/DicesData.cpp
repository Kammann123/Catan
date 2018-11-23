#include "DicesData.h"

DicesData::
DicesData(unsigned int fDice, unsigned int sDice) : CatanData(CatanData::Type::DICES), firstDice(fDice), secondDice(sDice) {}

DicesData::
DicesData() : CatanData(CatanData::Type::DICES) {
	this->firstDice = 0;
	this->secondDice = 0;
}

bool
DicesData::setFirstDice(unsigned int dice) {

	if (isValidDice(dice)) {
		this->firstDice = dice;
		return true;
	}
	else {
		return false;
	}
}

bool
DicesData::setSecondDice(unsigned int dice) {

	if (isValidDice(dice)) {
		this->secondDice = dice;
		return true;
	}
	else {
		return false;
	}
}

unsigned int
DicesData::getDices(void) const {
	return firstDice + secondDice;
}

unsigned int
DicesData::getFirstDice(void) const {
	return firstDice;
}

unsigned int
DicesData::getSecondDice(void) const {
	return secondDice;
}