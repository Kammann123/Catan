#include "MonopolyEvent.h"

MonopolyEvent::
MonopolyEvent(MonopolyPacket* packet) : CatanEvent(Events::MONOPOLY, Sources::NETWORKING, PlayerId::PLAYER_TWO), MonopolyData(packet->getResource()) {}

MonopolyEvent::
MonopolyEvent(ResourceId resource, PlayerId player) : CatanEvent(Events::MONOPOLY, Sources::GUI, player), MonopolyData(resource) {}