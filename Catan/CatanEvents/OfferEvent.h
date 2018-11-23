#pragma once

#include "CatanEvent.h"

#include "../CatanNetworking/NetworkPackets/OfferPacket.h"

#include <list>

using namespace std;

/* 
* OfferEvent
* Evento para realizar una oferta de cambio de cartas
*/
class OfferEvent : public CatanEvent{
public:
	OfferEvent(OfferPacket* packet);
	OfferEvent(list<ResourceId> given, list<ResourceId> recv, PlayerId player);
	~OfferEvent(void);

	/* Getter */
	list<ResourceId>& getGiven(void);
	list<ResourceId>& getRecv(void);
private:
	list<ResourceId> given;
	list<ResourceId> recv;
};