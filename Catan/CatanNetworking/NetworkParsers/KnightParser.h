#pragma once

#include "ParserStatus.h"

#include "../NetworkPackets/KnightPacket.h"

/*
* KnightParser
* Convierte la secuencia de bytes de la comunicacion al paquete de datos validando!
*/
class KnightParser : public ParserFsm {
public:
	/* Eventos del parser */
	enum Events : EventType { HEADER, COORD, OTHER };

	class HeaderEvent : public Event {
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class CoordEvent : public Event {
		CoordEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::COORD; }
	};

	class OtherEvent : public Event {
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType { HEAD, MOVE };

	/*
	* generateEvent
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/* Rutinas de accion */
	void init(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	KnightParser(void) : ParserFsm(&fsmTable[0][0], 2, 3, States::HEAD), packet(nullptr) {}
private:
	KnightPacket * packet;

	const FsmCell fsmTable[2][3] = {
		// HEADER COORD OTHER
		{ {States::MOVE, TX(KnightParser, init)},{States::HEAD, TX(KnightParser, error)},{ States::HEAD, TX(KnightParser, error) } },	// HEADER STATE
		{ { States::HEAD, TX(KnightParser, error) },{States::HEAD, TX(KnightParser, done)},{ States::HEAD, TX(KnightParser, error) } }	// MOVE STATE
	};

};