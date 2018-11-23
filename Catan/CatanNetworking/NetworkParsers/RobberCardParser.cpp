#include "RobberCardParser.h"

GenericEvent* RobberCardParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::ROBBER_CARDS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (byte > 0 && state == States::COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else if (isResourceValue(byte) && count > 1 && state == States::RESOURCES) {
		newEvent = new ResourceEvent(byte);
	}
	else if (isResourceValue(byte) && count == 1 && state == States::RESOURCES) {
		newEvent = new LastResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void RobberCardParser::
init(GenericEvent* event) {
	this->packet = new RobberCardPacket();
	this->count = 0;
}

void RobberCardParser::
setContext(GenericEvent* event) {
	this->count = ((NumberEvent*)event)->getData();
}

void RobberCardParser::
setResource(GenericEvent* event) {
	this->packet->setResource((ResourceId)((ResourceEvent*)event)->getData());
	this->count--;
}

void RobberCardParser::
done(GenericEvent* event) {
	this->packet->setResource((ResourceId)((LastResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->count = 0;
	this->packet = nullptr;
}

void RobberCardParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("RobberCardParser - Error en el formato del mensaje!");

	this->count = 0;
	delete this->packet;
}