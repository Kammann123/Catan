#include "CatanEvent.h"

CatanEvent::
CatanEvent(NetworkPacket* packet) {
	this->source = Sources::NETWORKING;
	this->player = PlayerId::PLAYER_TWO;

	switch (packet->getHeader()) {
		case PacketHeader::PASS:
			this->event = Events::PASS;
			break;
		case PacketHeader::QUIT:
			this->event = Events::QUIT;
			break;
		case PacketHeader::ERROR: default:
			this->event = Events::ERROR;
			break;
	}
}

CatanEvent::
CatanEvent(Events event, Sources source, PlayerId player) {

	this->getEvent = event;
	this->source = source;
	this->player = player;
}

CatanEvent::
~CatanEvent() {}

CatanEvent::Events 
CatanEvent::getEvent(void) const {
	return this->event;
}

CatanEvent::Sources
CatanEvent::getSource(void) const {
	return this->source;
}

PlayerId
CatanEvent::getPlayer(void) const {
	return this->player;
}