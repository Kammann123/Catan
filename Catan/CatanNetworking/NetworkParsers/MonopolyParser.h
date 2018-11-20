#pragma once

#include "ParserStatus.h"

#include "../NetworkPackets/MonopolyPacket.h"

/*
* MonopolyParser
* Paquete de datos de la secuencia de bytes de comunicacion
*/
class MonopolyParser : public ParserFsm {
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
	enum States : StateType { HEAD, ASK_RESOURCE };

	/*
	* generateEvent
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/* Rutinas de acciones */
	void init(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	MonopolyParser() : ParserFsm(&fsmTable[0][0], 2, 3, States::HEAD), packet(nullptr) {}

private:
	MonopolyPacket * packet;

	const FsmCell fsmTable[2][3] = {
		// HEADER RESOURCE OTHER
		{ {States::ASK_RESOURCE, TX(MonopolyParser, init)},{ States::HEAD, TX(MonopolyParser, error) },{States::HEAD, TX(MonopolyParser, error)} },	// HEADER state
		{ { States::HEAD, TX(MonopolyParser, error) },{States::HEAD, TX(MonopolyParser, done)},{ States::HEAD, TX(MonopolyParser, error) } }	// ASK RESOURCE state
	};
};