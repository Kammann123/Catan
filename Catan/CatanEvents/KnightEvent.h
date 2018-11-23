#pragma once

#include "CatanEvent.h"
#include "../CatanData/KnightData.h"
#include "../CatanNetworking/NetworkPackets/KnightPacket.h"

/*
* KnightEvent
* Evento de uso de la carta de desarrollo Knight
*/
class KnightEvent : public CatanEvent, public KnightData {
public:
	/* Constructores */
	KnightEvent(KnightPacket* packet);
	KnightEvent(unsigned char coord, PlayerId player);
};