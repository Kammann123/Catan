#pragma once

#include "CatanEvent.h"

#include "../CatanData/YOPData.h"
#include "../CatanNetworking/NetworkPackets/YOPPacket.h"

/*
* YOPEvent
* Evento para hacer uso de la carta Years Of Plenty
*/
class YOPEvent : public CatanEvent, public YOPData {
public:
	/* Constructores */
	YOPEvent(YOPPacket* packet);
	YOPEvent(ResourceId fRes, ResourceId sRes, PlayerId player);
};