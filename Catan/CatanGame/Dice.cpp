#include "Dice.h"

Dice::Dice(CatanGame * game)
{
	this->game = game;
}

void 
Dice::setValue(unsigned int value)
{
	this->value = value;
}

unsigned int
Dice::getValue(void)
{
	return value;
}