#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/BankPacket.h"
#include "../CatanData/BankData.h"

/*
* BankEvent
* Evento para realizar un cambio de cartas con banco.
*/
class BankEvent : public CatanEvent, public BankData {
public:
	/* Constructores y destructores */
	BankEvent(BankPacket* packet);
	BankEvent(list<ResourceId> given, list<ResourceId> recv);
	BankEvent(list<ResourceCard*> given, list<ResourceCard*> recv);
	~BankEvent();
};