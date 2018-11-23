#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/DicesPacket.h"
#include "../CatanData/DicesData.h"

/*
* DicesEvent
* Evento para tirar dados.
*/
class DicesEvent : public CatanEvent, public DicesData{
public:
	/* Constructores y destructores */
	DicesEvent(DicesPacket* packet);
	DicesEvent(unsigned int firstDice, unsigned int secondDice, PlayerId player);
	~DicesEvent(void);
};