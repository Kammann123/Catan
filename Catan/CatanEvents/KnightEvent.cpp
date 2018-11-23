#include "KnightEvent.h"

KnightEvent::
KnightEvent(KnightPacket* packet) : CatanEvent(Events::KNIGHT, Sources::NETWORKING, PlayerId::PLAYER_TWO), KnightData(packet->getCoord()) {}

KnightEvent::
KnightEvent(unsigned char coord, PlayerId player) : CatanEvent(Events::KNIGHT, Sources::GUI, player), KnightData(coord) {}