#pragma once

#include "CatanEvent.h"

/*
* DicesEvent
* Evento para tirar dados.
*/
class DicesEvent : public CatanEvent {
public:
	/* Constructores y destructores */
	DicesEvent(unsigned int firstDice, unsigned int secondDice);
	DicesEvent(unsigned int dices);
	~DicesEvent(void);

	/* Getter */
	unsigned int getDices(void) const;
private:
	unsigned int dices;
};