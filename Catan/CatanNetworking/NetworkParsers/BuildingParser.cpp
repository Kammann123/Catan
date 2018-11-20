#include "BuildingParser.h"

GenericEvent* BuildingParser::
generateEvent(unsigned char byte) {

	GenericEvent* newEvent = nullptr;

	if ( (byte == (unsigned char)PacketHeader::SETTLEMENT || byte == (unsigned char)PacketHeader::CITY || byte == (unsigned char)PacketHeader::ROAD) && state == States::HEAD ) {
		newEvent = new HeaderEvent(byte);
	}
	else if (byte > 0 && state == States::COUNT) {
		newEvent = new NumberEvent(byte);
	}
	else if ((isMapPosition(byte) || isSeaPosition(byte)) && count > 1 && state == States::COORDS) {
		newEvent = new CoordEvent(byte);
	}
	else if ((isMapPosition(byte) || isSeaPosition(byte)) && count == 1 && state == States::COORDS){
		newEvent = new LastCoordEvent(byte);
	}
	else {
		newEvent = new OtherEvent(byte);
	}

	return newEvent;
}

void BuildingParser::
init(GenericEvent* event) {
	this->packet = new BuildingPacket((PacketHeader)((HeaderEvent*)event)->getData());
	this->count = 0;
}

void BuildingParser::
setContext(GenericEvent* event) {
	this->count = ((NumberEvent*)event)->getData();
}

void BuildingParser::
setCoord(GenericEvent* event) {
	this->packet->setCoords(((CoordEvent*)event)->getData());
	this->count--;
}

void BuildingParser::
done(GenericEvent* event) {
	this->packet->setCoords(((LastCoordEvent*)event)->getData());

	fsmEvent = new DoneEvent(this->packet);

	this->count = 0;
	this->packet = nullptr;
}

void BuildingParser::
error(GenericEvent* event) {
	fsmEvent = new ErrorEvent("BuildingParser - Error en el formato del mensaje!");

	this->count = 0;
	delete this->packet;
}