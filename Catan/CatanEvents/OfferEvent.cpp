#include "OfferEvent.h"

OfferEvent::
OfferEvent(OfferPacket* packet) : CatanEvent(Events::OFFER_TRADE, Sources::NETWORKING, PlayerId::PLAYER_TWO), OfferData(packet->getGiven(), packet->getRecv()){}

OfferEvent::
OfferEvent(list<ResourceId> given, list<ResourceId> recv, PlayerId player) : CatanEvent(Events::OFFER_TRADE, Sources::GUI, player), OfferData(given, recv) {}