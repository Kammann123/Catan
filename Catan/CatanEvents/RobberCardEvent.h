#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/RobberCardPacket.h"

#include <list>

using namespace std;

/*
* RobberCardEvent
* Evento para realizar el descarte de una seleccion de cartas.
*/
class RobberCardEvent : public CatanEvent {
public:
	/* Constructores y destructores */
	RobberCardEvent(RobberCardPacket* packet);
	RobberCardEvent(list<ResourceId> res);
	~RobberCardEvent();

	/* Getter */
	list<ResourceId>& getResources(void);
private:
	list<ResourceId> res;
};