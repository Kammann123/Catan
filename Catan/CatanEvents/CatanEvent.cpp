#include "CatanEvent.h"

CatanEvent::
CatanEvent(Events event, Sources source, PlayerId player) {
	this->event = event;
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