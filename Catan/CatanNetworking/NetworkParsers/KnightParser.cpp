#include "KnightParser.h"

GenericEvent* 
KnightParser::generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::KNIGHT && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (isMapPosition(byte) && state == States::MOVE) {
		newEvent = new CoordEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void
KnightParser::init(GenericEvent* event) {
	this->packet = new KnightPacket();
}

void
KnightParser::done(GenericEvent* event) {
	this->packet->setCoord(((CoordEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void
KnightParser::error(GenericEvent* event) {
	delete this->packet;

	fsmEvent = new ErrorEvent("KnightParser - Error en el formato del mensaje!");
}