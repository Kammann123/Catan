#include "Dice.h"
#include "CatanGame.h"

#define DICES_SCALE_TIMER	5
#define DICES_LOOPS		3

using namespace std::placeholders;

Dice::
Dice(string id) : AnimationUI(id, 6) {
	this->value = 1;
	this->setMode(Mode::X_TIMES);
	this->setLoopTimes(DICES_LOOPS);
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