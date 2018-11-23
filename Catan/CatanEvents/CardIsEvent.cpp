#include "CardIsEvent.h"

CardIsEvent::
CardIsEvent(ResourceId resource, PlayerId player) : CatanEvent(Events::CARD_IS, Sources::GUI, player), CardIsData(resource) {}

CardIsEvent::
CardIsEvent(CardIsPacket* packet) : CatanEvent(Events::CARD_IS, Sources::NETWORKING, PlayerId::PLAYER_TWO), CardIsData(packet->getResource()) {}