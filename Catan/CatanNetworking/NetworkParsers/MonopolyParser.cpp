#include "MonopolyParser.h"

GenericEvent* 
MonopolyParser::generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if( byte == (unsigned char)PacketHeader::MONOPOLY && state == States::HEAD){
		newEvent = new HeaderEvent(byte);
	}
	else if (isResourceValue(byte) && state == States::ASK_RESOURCE) {
		newEvent = new ResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void 
MonopolyParser::init(GenericEvent* event) {
	this->packet = new MonopolyPacket();
}

void 
MonopolyParser::done(GenericEvent* event){
	this->packet->setResource(((ResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
}

void 
MonopolyParser::error(GenericEvent* event) {
	delete this->packet;

	fsmEvent = new ErrorEvent("MonopolyParser - Error en el formato del mensaje!");
}