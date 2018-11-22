#include "BuildingEvent.h"

BuildingEvent::
BuildingEvent(BuildingPacket* packet) : CatanEvent(Events::BUILDING, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->coords = packet->getCoords();
}

BuildingEvent::
BuildingEvent(string& coords) : CatanEvent(Events::BUILDING, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->coords = coords;
}

BuildingEvent::
~BuildingEvent() {}

string
BuildingEvent::getCoords(void) const {
	return this->coords;
}