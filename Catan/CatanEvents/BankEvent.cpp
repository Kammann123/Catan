#include "BankEvent.h"

BankEvent::
BankEvent(BankPacket* packet) : CatanEvent(Events::BANK_TRADE, Sources::NETWORKING, PlayerId::PLAYER_TWO), BankData(packet->getGiven(), packet->getRecv()){}

BankEvent::
BankEvent(list<ResourceId> given, list<ResourceId> recv) : CatanEvent(Events::BANK_TRADE, Sources::GUI, PlayerId::PLAYER_ONE), BankData(given, recv){}

BankEvent::
~BankEvent() {}