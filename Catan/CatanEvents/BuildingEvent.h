#pragma once

#include "CatanEvent.h"
#include "../CatanGame/Building.h"

#include "../CatanNetworking/NetworkPackets/BuildingPacket.h"

/*
* BuildingEvent
* Evento para realizar una construccion.
*/
class BuildingEvent : public CatanEvent {
public:
	/* Constructores y destructores */
	BuildingEvent(BuildingPacket* packet);
	BuildingEvent(string& coords, BuildingType type);
	~BuildingEvent();
	
	/* Getter */
	string getCoords(void) const;
private:
	string coords;
	BuildingType type;
};