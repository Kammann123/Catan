#include "DicesEvent.h"

DicesEvent::
DicesEvent(DicesPacket* packet) : CatanEvent(Events::THROW_DICES, Sources::NETWORKING, PlayerId::PLAYER_TWO), DicesData(packet->getFirstDice(), packet->getSecondDice()) {}

DicesEvent::
DicesEvent(unsigned int firstDice, unsigned int secondDice, PlayerId player) : CatanEvent(Events::THROW_DICES, Sources::GUI, player), DicesData(firstDice, secondDice) {}

DicesEvent::
~DicesEvent(void) {}