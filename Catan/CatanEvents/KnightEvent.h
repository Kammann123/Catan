#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/KnightPacket.h"

/*
* KnightEvent
* Evento de uso de la carta de desarrollo Knight
*/
class KnightEvent : public CatanEvent, public KnightData {
public:
	/* Constructores */
	KnightEvent(KnightPacket* packet);
	KnightEvent(Coord coord, PlayerId player);
};