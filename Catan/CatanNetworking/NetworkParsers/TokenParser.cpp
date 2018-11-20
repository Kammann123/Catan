#include "TokenParser.h"

GenericEvent* TokenParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::CIRCULAR_TOKENS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (nextIndex != 'S' && state == States::MAP) {
		if (isValidToken(byte)) {
			newEvent = new TokenEvent(byte);
		}
		else {
			newEvent = new OtherEvent(byte);
		}
	}
	else if (nextIndex == 'S' && state == States::MAP) {
		if (isValidToken(byte)) {
			newEvent = new LastTokenEvent(byte);
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

void TokenParser::
init(GenericEvent* event) {
	this->packet = new TokenPacket();
	this->nextIndex = 'A';
}

void TokenParser::
setToken(GenericEvent* event) {
	this->packet->setToken(this->nextIndex, ((TokenEvent*)event)->getData());
	this->nextIndex++;
}

void TokenParser::
done(GenericEvent* event) {
	this->packet->setToken(this->nextIndex, ((LastTokenEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->nextIndex = 'A';
}

void TokenParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("TokenParser - Error en el formato recibido!");

	delete this->packet;
	this->nextIndex = 'A';
}