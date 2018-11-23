#include "YOPEvent.h"

YOPEvent::
YOPEvent(ResourceId fRes, ResourceId sRes, PlayerId player) : CatanEvent(Events::YOP, Sources::GUI, player), YOPData(fRes, sRes) {}

YOPEvent::
YOPEvent(YOPPacket* packet) : CatanEvent(Events::YOP, Sources::NETWORKING, PlayerId::PLAYER_TWO), YOPData(packet->getFirstResource(), packet->getSecondResource()) {}