#include "RobberCardEvent.h"

RobberCardEvent::
RobberCardEvent(RobberCardPacket* packet) : CatanEvent(Events::ROBBER_CARDS, Sources::NETWORKING, PlayerId::PLAYER_TWO) {
	this->res = packet->getResources();
}

RobberCardEvent::
RobberCardEvent(list<ResourceId> res) : CatanEvent(Events::ROBBER_CARDS, Sources::GUI, PlayerId::PLAYER_ONE) {
	this->res = res;
}

RobberCardEvent::
~RobberCardEvent(void) {}

list<ResourceId>&
RobberCardEvent::getResources(void) {
	return this->res;
}