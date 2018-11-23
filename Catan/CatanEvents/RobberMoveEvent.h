#pragma once

#include "CatanEvent.h"

#include "../CatanNetworking/NetworkPackets/RobberMovePacket.h"

#include "../CatanData/RobberMoveData.h"

/*
* RobberMoveEvent
* Evento para mover el ladron!
*/
class RobberMoveEvent : public CatanEvent, public RobberMoveData {
public:
	/* Constructor y destructor */
	RobberMoveEvent(RobberMovePacket* packet);
	RobberMoveEvent(unsigned char coord, PlayerId player);
	~RobberMoveEvent(void);
};