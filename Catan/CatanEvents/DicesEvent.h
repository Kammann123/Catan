#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/DicesPacket.h"

/*
* DicesEvent
* Evento para tirar dados.
*/
class DicesEvent : public CatanEvent {
public:
	/* Constructores y destructores */
	DicesEvent(DicesPacket* packet);
	DicesEvent(unsigned int firstDice, unsigned int secondDice, PlayerId player);
	DicesEvent(unsigned int dices, PlayerId player);
	~DicesEvent(void);

	/* Getter */
	unsigned int getDices(void) const;
private:
	unsigned int dices;
};