#include "RobberCardEvent.h"

RobberCardEvent::
RobberCardEvent(RobberCardPacket* packet) : CatanEvent(Events::ROBBER_CARDS, Sources::NETWORKING, PlayerId::PLAYER_TWO), RobberCardData(packet->getResources()) {}

RobberCardEvent::
RobberCardEvent(list<ResourceId> res, PlayerId player) : CatanEvent(Events::ROBBER_CARDS, Sources::GUI, player), RobberCardData(res) {}

RobberCardEvent::
~RobberCardEvent(void) {}