#include "YOPParser.h"

GenericEvent*
YOPParser::generateEvent(unsigned char byte) {
	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::YEARS_OF_PLENTY && state == States::HEAD ) {
		newEvent = new HeaderEvent(byte);
	}
	else if (isResourceValue(byte) && (state == States::FIRST_RESOURCE || state == States::SECOND_RESOURCE)) {
		newEvent = new ResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}
	return newEvent;
}

void 
YOPParser::init(GenericEvent* event) {
	this->packet = new YOPPacket();
}

void 
YOPParser::setFirstResource(GenericEvent* event) {
	this->packet->setFirstResource((ResourceId)((ResourceEvent*)event)->getData());
}

void 
YOPParser::done(GenericEvent* event) {
	this->packet->setSecondResource((ResourceId)((ResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void 
YOPParser::error(GenericEvent* event) {
	delete this->packet;

	fsmEvent = new ErrorEvent("YOPParser - Error en el formato del mensaje!");
}