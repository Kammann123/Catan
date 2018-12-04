#include "Dice.h"
#include "CatanGame.h"

#define DICES_SCALE_TIMER	10

using namespace std::placeholders;

Dice::
Dice(string id) : AnimationUI(id, 6) {
	this->setScaleTimer(DICES_SCALE_TIMER);
	this->setFrameAction(bind(&Dice::random, this, _1));
}

void 
Dice::random(void* data) {
	this->value = RANDOM_DICE;
}

unsigned int
Dice::getValue(void)
{
	return value;
}