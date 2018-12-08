#pragma once

#include "UIModelContainer.h"

class CounterUI : public FrameUI {
public:

	/*
	* CounterUI - Se construye con el id y una cantidad
	* maxima de contador.
	*/
	CounterUI(string id, unsigned int max);

	/*********************
	* Interfaz de acceso *
	*********************/
	unsigned int getValue(void);
	void reset(void);
	void plusValue(unsigned int value);
	void minusValue(unsigned int value);

private:
	unsigned int counter;
	unsigned int max;
};