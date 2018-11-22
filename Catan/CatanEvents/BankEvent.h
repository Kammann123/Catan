#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/BankPacket.h"

#include <list>

using namespace std;

/*
* BankEvent
* Evento para realizar un cambio de cartas con banco.
*/
class BankEvent : CatanEvent {
public:
	/* Constructores y destructores */
	BankEvent(BankPacket* packet);
	BankEvent(list<ResourceId> given, list<ResourceId> recv);
	~BankEvent();

	/* Getter */
	list<ResourceId>& getGivenResources(void);
	list<ResourceId>& getReceivedResources(void);
private:
	list<ResourceId> givenResource;
	list<ResourceId> receivedResource;
};