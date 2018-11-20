#include "MapParser.h"

GenericEvent* MapParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if (byte == (unsigned char)PacketHeader::MAP_IS && state == States::HEAD) {
		newEvent = new HeaderEvent(byte);
	}
	else if (nextIndex == 'S' && state == States::MAP) {
		if (isMapValue(byte)) {
			newEvent = new LastIndexEvent(byte);
		}
		else {
			newEvent = new OtherEvent(byte);
		}
	}
	else if (nextIndex != 'S' && state == States::MAP) {
		if (isMapValue(byte)) {
			newEvent = new IndexEvent(byte);
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

void MapParser::
init(GenericEvent* event) {
	this->packet = new MapPacket();
	this->nextIndex = '0';
}

void MapParser::
saveMap(GenericEvent* event) {
	this->packet->setMapValue(this->nextIndex, ((IndexEvent*)event)->getData());

	if (this->nextIndex == '5') {
		this->nextIndex = 'A';
	}
	else {
		this->nextIndex++;
	}
}

void MapParser::
done(GenericEvent* event) {
	this->packet->setMapValue(this->nextIndex, ((LastIndexEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->packet = nullptr;
	this->nextIndex = '0';
}

void MapParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("MapParser - Error en formato del mensaje!");

	delete this->packet;
	this->nextIndex = '0';
}