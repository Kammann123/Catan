#include "OfferParser.h"

GenericEvent* OfferParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::OFFER_TRADE && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (byte > 0 && state == States::GIVEN_COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else if (byte > 0 && state == States::RECV_COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else if (isResourceValue(byte) && givenCount > 1 && state == States::GIVEN) {
		newEvent = new ResourceEvent(byte);
	}
	else if (isResourceValue(byte) && givenCount == 1 && state == States::GIVEN) {
		newEvent = new LastResourceEvent(byte);
	}
	else if (isResourceValue(byte) && recvCount > 1 && state == States::RECV) {
		newEvent = new ResourceEvent(byte);
	}
	else if (isResourceValue(byte) && recvCount == 1 && state == States::RECV) {
		newEvent = new LastResourceEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void OfferParser::
init(GenericEvent* event) {
	this->packet = new OfferPacket();
	this->givenCount = 0;
	this->recvCount = 0;
}

void OfferParser::
setGivenCount(GenericEvent* event) {
	this->givenCount = ((NumberEvent*)event)->getData();
}

void OfferParser::
setRecvCount(GenericEvent* event) {
	this->recvCount = ((NumberEvent*)event)->getData();
}

void OfferParser::
setGiven(GenericEvent* event) {
	this->packet->setGiven((ResourceId)((ResourceEvent*)event)->getData());
	this->givenCount--;
}

void OfferParser::
setRecv(GenericEvent* event) {
	this->packet->setRecv((ResourceId)((ResourceEvent*)event)->getData());
	this->recvCount--;
}

void OfferParser::
done(GenericEvent* event) {
	this->packet->setRecv((ResourceId)((ResourceEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->givenCount = 0;
	this->recvCount = 0;
}

void OfferParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("OfferParser - Error en el formato del mensaje!");

	delete this->packet;
	this->givenCount = 0;
	this->recvCount = 0;
}