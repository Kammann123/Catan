#include "DicesParser.h"

GenericEvent* DicesParser::
generateEvent(unsigned char byte) {
	
	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::DICES_ARE && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if ( state == States::FIRST_DICE || state == States::SECOND_DICE ) {
		if (isValidDice(byte - '0')) {
			newEvent = new DiceEvent(byte);
		}
		else {
			newEvent = new OtherEvent(byte);
		}
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void DicesParser::
init(GenericEvent* event) {
	this->packet = new DicesPacket();
}

void DicesParser::
setDice(GenericEvent* event) {
	this->packet->setFirstDice(((DiceEvent*)event)->getData() - '0');
}

void DicesParser::
done(GenericEvent* event) {
	this->packet->setSecondDice(((DiceEvent*)event)->getData() - '0');

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void DicesParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("DicesParser - Error en el formato del mensaje!");

	delete this->packet;
}