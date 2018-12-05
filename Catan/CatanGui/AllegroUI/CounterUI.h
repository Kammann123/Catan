#pragma once

#include "UIModelContainer.h"

class CounterUI : public UIModelContainer {
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
	void reset(void* data);
	void plusValue(void* data);
	void minusValue(void* data);

private:
	unsigned int counter;
	unsigned int max;
};