#include "DevCardParser.h"

GenericEvent* DevCardParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::DEV_CARDS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (nextIndex < 24 && state == States::CARDS ) {
		if (isDevCard(byte)) {
			newEvent = new CardEvent(byte);
		}
		else {
			newEvent = new OtherEvent(byte);
		}
	}
	else if (nextIndex == 24 && state == States::CARDS) {
		if (isDevCard(byte)) {
			newEvent = new LastCardEvent(byte);
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

void DevCardParser::
init(GenericEvent* event) {
	this->nextIndex = 0;
	this->packet = new DevCardPacket();
}

void DevCardParser::
setCard(GenericEvent* event) {
	this->packet->setCard((DevCardId)((CardEvent*)event)->getData());
	this->nextIndex++;
}

void DevCardParser::
done(GenericEvent* event) {
	this->packet->setCard((DevCardId)((LastCardEvent*)event)->getData());
	
	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->nextIndex = 0;
}

void DevCardParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("DevCardParser - Error del formato del mensaje!");

	delete this->packet;
	this->nextIndex = 0;
}
