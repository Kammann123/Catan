#pragma once

#include "NameParser.h"

GenericEvent* NameParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	/* Me fijo que tipo de byte es */
	if (byte == (unsigned char)PacketHeader::NAME_IS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (((byte >= 'a' && byte <= 'z') || (byte >= 'A' && byte <= 'Z')) && state == States::NAME) {

		/* Verifico estado actual de fsm */
		if (count == 1) {
			newEvent = new LastLetterEvent(byte);
		}
		else {
			newEvent = new LetterEvent(byte);
		}
	}
	else if (byte > 0 && state == States::COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void NameParser::
init(GenericEvent* event) {

	this->packet = new NamePacket();
}

void NameParser::
setContext(GenericEvent* event) {

	NumberEvent* ev = (NumberEvent*)event;
	this->count = ev->getData();
}

void NameParser::
setName(GenericEvent* event) {
	
	LetterEvent* ev = (LetterEvent*)event;
	this->packet->setName(ev->getData());
	this->count--;
}

void NameParser::
done(GenericEvent* event) {

	LastLetterEvent* ev = (LastLetterEvent*)event;
	this->packet->setName(ev->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->count = 0;
}

void NameParser::
error(GenericEvent* event) {

	fsmEvent = new ErrorEvent("NameParser - Error en formato del mensaje!");

	delete this->packet;
	this->count = 0;
}