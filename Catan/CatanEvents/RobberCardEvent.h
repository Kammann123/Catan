#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/RobberCardPacket.h"
#include "../CatanData/RobberCardData.h"

/*
* RobberCardEvent
* Evento para realizar el descarte de una seleccion de cartas.
*/
class RobberCardEvent : public CatanEvent, public RobberCardData{
public:
	/* Constructores y destructores */
	RobberCardEvent(RobberCardPacket* packet);
	RobberCardEvent(list<ResourceId> res, PlayerId player);
	RobberCardEvent(list<ResourceCard*> res, PlayerId player);
};