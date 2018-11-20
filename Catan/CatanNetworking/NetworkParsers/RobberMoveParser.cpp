#include "RobberMoveParser.h"

GenericEvent* RobberMoveParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::ROBBER_MOVE && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (isMapPosition(byte) && state == States::MOVE) {
		newEvent = new PositionEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void RobberMoveParser::
init(GenericEvent* event) {
	this->packet = new RobberMovePacket();
}

void RobberMoveParser::
done(GenericEvent* event) {
	this->packet->setCoord(((PositionEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void RobberMoveParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("RobberMoveParser - Error en el formato del mensaje!");

	delete this->packet;
}