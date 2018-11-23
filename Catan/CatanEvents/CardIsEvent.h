#pragma once

#include "CatanEvent.h"

#include "../CatanData/CardIsData.h"
#include "../CatanNetworking/NetworkPackets/CardIsPacket.h"

/*
* CardIsEvent
* Evento para entregar una carta robada por un Knight
*/
class CardIsEvent : public CatanEvent, public CardIsData {
public:
	/* Constructores */
	CardIsEvent(CardIsPacket* packet);
	CardIsEvent(ResourceId resource, PlayerId player);
};