#include "KnightEvent.h"

KnightEvent::
KnightEvent(KnightPacket* packet) : CatanEvent(Events::KNIGHT, Sources::NETWORKING, PlayerId::PLAYER_TWO), KnightData(*(KnightData*)packet) {}

KnightEvent::
KnightEvent(Coord coord, PlayerId player) : CatanEvent(Events::KNIGHT, Sources::GUI, player), KnightData(coord) {}