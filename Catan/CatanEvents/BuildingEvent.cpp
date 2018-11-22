#include "BuildingEvent.h"

BuildingEvent::
BuildingEvent(BuildingPacket* packet) : CatanEvent(Events::BUILDING, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->coords = packet->getCoords();
	
	switch (packet->getHeader() ){
		case PacketHeader::SETTLEMENT:
			this->type = BuildingType::SETTLEMENT;
			break;
		case PacketHeader::CITY:
			this->type = BuildingType::CITY;
			break;
		case PacketHeader::ROAD:
			this->type = BuildingType::ROAD;
			break;
	}
}

BuildingEvent::
BuildingEvent(string& coords, BuildingType type) : CatanEvent(Events::BUILDING, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->coords = coords;
	this->type = type;
}

BuildingEvent::
~BuildingEvent() {}

string
BuildingEvent::getCoords(void) const {
	return this->coords;
}