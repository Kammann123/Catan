#pragma once

#include "CatanEvent.h"

#include "../CatanNetworking/NetworkPackets/OfferPacket.h"
#include "../CatanData/OfferData.h"

/* 
* OfferEvent
* Evento para realizar una oferta de cambio de cartas
*/
class OfferEvent : public CatanEvent, public OfferData{
public:
	OfferEvent(OfferPacket* packet);
	OfferEvent(list<ResourceId> given, list<ResourceId> recv, PlayerId player);
	~OfferEvent(void);
};