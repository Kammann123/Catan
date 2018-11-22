#pragma once

#include "CatanEvent.h"

#include "../CatanNetworking/NetworkPackets/RobberMovePacket.h"

/*
* RobberMoveEvent
* Evento para mover el ladron!
*/
class RobberMoveEvent : public CatanEvent {
public:
	/* Constructor y destructor */
	RobberMoveEvent(RobberMovePacket* packet);
	RobberMoveEvent(unsigned char coord);
	~RobberMoveEvent(void);

	/* Getter */
	unsigned char getCoord(void) const;
private:
	unsigned char coord;
};