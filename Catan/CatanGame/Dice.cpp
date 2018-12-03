#include "Dice.h"

Dice::Dice(int64_t maxTimerCount, Mode mode_, string id, size_t width, size_t height, bool dragMode, bool holdMode, int timesToLoop): AnimationUI (maxTimerCount, mode_, timesToLoop,id, width, height, dragMode, holdMode)
{}

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