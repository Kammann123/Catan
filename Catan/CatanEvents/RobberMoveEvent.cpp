#include "RobberMoveEvent.h"

RobberMoveEvent::
RobberMoveEvent(RobberMovePacket* packet) : CatanEvent(Events::ROBBER_MOVE, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->coord = packet->getCoord();
}

RobberMoveEvent::
RobberMoveEvent(unsigned char coord) : CatanEvent(Events::ROBBER_MOVE, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->coord = coord;
}

RobberMoveEvent::
~RobberMoveEvent() {}

unsigned char
RobberMoveEvent::getCoord(void) const {
	return this->coord;
}