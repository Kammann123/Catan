#include "BankEvent.h"

BankEvent::
BankEvent(BankPacket* packet) : CatanEvent(Events::BANK_TRADE, Sources::NETWORKING, PlayerId::PLAYER_TWO), BankData(packet->getGiven(), packet->getRecv()){}

BankEvent::
BankEvent(list<ResourceId> given, list<ResourceId> recv, PlayerId player) : CatanEvent(Events::BANK_TRADE, Sources::GUI, player), BankData(given, recv) {}

BankEvent::
~BankEvent() {}