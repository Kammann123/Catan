#include "CounterUI.h"

CounterUI::
CounterUI(string id, unsigned int max) : FrameUI(id, 0, 0) {
	this->counter = 0;
	this->max = max;
}

unsigned int 
CounterUI::getValue(void) {
	return counter;
}

void
CounterUI::reset(void) {
	counter = 0;
}

void
CounterUI::plusValue(unsigned int value) {
	if (counter < max) {
		counter += value;
	}
}

void
CounterUI::minusValue(unsigned int value) {
	if (counter) {
		counter -= value;
	}
}