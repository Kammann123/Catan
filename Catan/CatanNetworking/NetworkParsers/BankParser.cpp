#include "BankParser.h"

GenericEvent* BankParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::BANK_TRADE && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (byte > 0 && state == States::COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else if (isResourceValue(byte) && count > 1 && state == States::GIVEN) {
		newEvent = new ResourceEvent(byte);
	}
	else if (isResourceValue(byte) && count == 1 && state == States::GIVEN) {
		newEvent = new LastResourceEvent(byte);
	}
	else if (isResourceValue(byte) && state == States::RECEIVED) {
		newEvent = new ResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void BankParser::
init(GenericEvent* event) {
	this->count = 0;
	this->packet = new BankPacket();

}

void BankParser::
setContext(GenericEvent* event) {
	this->count = ((NumberEvent*)event)->getData();
}

void BankParser::
setGiven(GenericEvent* event) {
	this->packet->addGivenResources((ResourceId)((ResourceEvent*)event)->getData());
	this->count--;
}

void BankParser::
done(GenericEvent* event) {
	this->packet->addReceivedResources((ResourceId)((ResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->count = 0;
}

void BankParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("BankParser - Error en el formato del mensaje!");

	delete this->packet;
	this->count = 0;
}