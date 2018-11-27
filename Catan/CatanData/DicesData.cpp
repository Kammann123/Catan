#include "DicesData.h"

DicesData::
DicesData(unsigned char fDice, unsigned char sDice) : CatanData(CatanData::Type::DICES), firstDice(fDice), secondDice(sDice) {}

DicesData::
DicesData() : CatanData(CatanData::Type::DICES) {
	this->firstDice = 0;
	this->secondDice = 0;
}

bool
DicesData::setFirstDice(unsigned char dice) {

	if (isValidDice(dice)) {
		this->firstDice = dice;
		return true;
	}
	else {
		return false;
	}
}

bool
DicesData::setSecondDice(unsigned char dice) {

	if (isValidDice(dice)) {
		this->secondDice = dice;
		return true;
	}
	else {
		return false;
	}
}

unsigned char
DicesData::getDices(void) const {
	return firstDice + secondDice - '0' - '0';
}

unsigned char
DicesData::getFirstDice(void) const {
	return firstDice - '0';
}

unsigned char
DicesData::getSecondDice(void) const {
	return secondDice - '0';
}