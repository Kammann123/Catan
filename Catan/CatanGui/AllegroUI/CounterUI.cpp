#include "CounterUI.h"

CounterUI::
CounterUI(string id, unsigned int max) : UIModelContainer(id) {
	this->counter = 0;
	this->max = max;
}

unsigned int 
CounterUI::getValue(void) {
	return counter;
}

void
CounterUI::reset(void* data) {
	counter = 0;
}

void
CounterUI::plusValue(void* data) {
	if (counter < max) {
		counter++;
	}
}

void
CounterUI::minusValue(void* data) {
	if (counter) {
		counter--;
	}
}