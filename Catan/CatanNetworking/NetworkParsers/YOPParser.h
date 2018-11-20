#pragma once

#include "ParserStatus.h"

#include "../NetworkPackets/YOPPacket.h"

/*
* YOPParser
* Parsea en un paquete de datos la secuencia de bytes
*/
class YOPParser : public ParserFsm {
public:
	/* Eventos del parser */
	enum Events : EventType { HEADER, RESOURCE, OTHER };

	class HeaderEvent : public Event {
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class ResourceEvent : public Event {
		ResourceEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::RESOURCE; }
	};

	class OtherEvent : public Event {
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType { HEAD, FIRST_RESOURCE, SECOND_RESOURCE };

	/*
	* generateEvent
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/* Rutinas de accion */
	void init(GenericEvent* event);
	void setFirstResource(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	YOPParser(void) : ParserFsm(&fsmTable[0][0], 3, 3, States::HEAD), packet(nullptr) {}

private:
	YOPPacket * packet;

	const FsmCell fsmTable[3][3] = {
		// HEADER RESOURCE OTHER
		{ {States::FIRST_RESOURCE, TX(YOPParser, init)},{ States::HEAD, TX(YOPParser, error) },{States::HEAD, TX(YOPParser, error)} },	// HEADER STATE
		{ { States::HEAD, TX(YOPParser, error) },{States::SECOND_RESOURCE, TX(YOPParser, setFirstResource)},{ States::HEAD, TX(YOPParser, error) } },	// FIRST RES STATE
		{ { States::HEAD, TX(YOPParser, error) },{States::HEAD, TX(YOPParser, done)},{ States::HEAD, TX(YOPParser, error) } }	// SECOND RES STATE
	};
};