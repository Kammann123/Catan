#include "RobberMoveEvent.h"

RobberMoveEvent::
RobberMoveEvent(RobberMovePacket* packet) : CatanEvent(Events::ROBBER_MOVE, Sources::NETWORKING, PlayerId::PLAYER_TWO), RobberMoveData(packet->getCoord()) {}

RobberMoveEvent::
RobberMoveEvent(Coord coord, PlayerId player) : CatanEvent(Events::ROBBER_MOVE, Sources::GUI, player), RobberMoveData(coord) {}

RobberMoveEvent::
~RobberMoveEvent() {}