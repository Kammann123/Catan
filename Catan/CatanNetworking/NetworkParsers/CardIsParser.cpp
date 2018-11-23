#include "CardIsParser.h"

GenericEvent*
CardIdParser::generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::CARD_IS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (isResourceValue(byte) && state == States::CARD) {
		newEvent = new ResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void
CardIdParser::init(GenericEvent* event) {
	this->packet = new CardIsPacket();
}

void
CardIdParser::done(GenericEvent* event) {
	this->packet->setResource((ResourceId)((ResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void
CardIdParser::error(GenericEvent* event) {
	delete this->packet;

	fsmEvent = new ErrorEvent("CardIsParser - Error en el formato del mensaje!");
}