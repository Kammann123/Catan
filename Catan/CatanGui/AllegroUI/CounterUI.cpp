#include "CounterUI.h"

CounterUI::
CounterUI(string id, unsigned int max) : UIModelContainer(id) {
	this->counter = 0;
	this->max = max;
}

unsigned int getValue(void) {
	return counter;
}

void reset(void* data) {
	counter = 0;
}

void plusValue(void* data) {
	if (counter < max) {
		counter++;
	}
}

void minusValue(void* data) {
	if (counter) {
		counter--;
	}
}