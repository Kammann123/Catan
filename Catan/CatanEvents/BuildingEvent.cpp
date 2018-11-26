#include "BuildingEvent.h"

BuildingEvent::
BuildingEvent(BuildingPacket* packet) : CatanEvent(Events::BUILDING, Sources::NETWORKING, PlayerId::PLAYER_TWO), BuildingData(packet->getType(), packet->getCoords()) {}

BuildingEvent::
BuildingEvent(Coord coords, BuildingType type) : CatanEvent(Events::BUILDING, Sources::GUI, PlayerId::PLAYER_ONE), BuildingData(type, coords) {}

BuildingEvent::
~BuildingEvent() {}