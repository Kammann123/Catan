#pragma once

#include "CatanEvent.h"
#include "../CatanGame/Building.h"

#include "../CatanNetworking/NetworkPackets/BuildingPacket.h"
#include "../CatanData/BuildingData.h"

/*
* BuildingEvent
* Evento para realizar una construccion.
*/
class BuildingEvent : public CatanEvent, public BuildingData {
public:
	/* Constructores y destructores */
	BuildingEvent(BuildingPacket* packet);
	BuildingEvent(Coord coords, BuildingType type);
	~BuildingEvent();
};