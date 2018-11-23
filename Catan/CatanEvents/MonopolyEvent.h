#pragma once

#include "CatanEvent.h"
#include "../CatanData/MonopolyData.h"
#include "../CatanNetworking/NetworkPackets/MonopolyPacket.h"

/*
* MonopolyEvent
* Evento del uso de la carta de desarrollo Monopoly
*/
class MonopolyEvent : public CatanEvent, public MonopolyData {
public:

	/* Constructores */
	MonopolyEvent(MonopolyPacket* packet);
	MonopolyEvent(ResourceId resource, PlayerId player);
};