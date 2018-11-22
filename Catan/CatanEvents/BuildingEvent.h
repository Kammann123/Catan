#pragma once

#include "CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/BuildingPacket.h"

/*
* BuildingEvent
* Evento para realizar una construccion.
*/
class BuildingEvent : public CatanEvent {
public:
	/* Constructores y destructores */
	BuildingEvent(BuildingPacket* packet);
	BuildingEvent(string& coords);
	~BuildingEvent();
	
	/* Getter */
	string getCoords(void) const;
private:
	string coords;
};