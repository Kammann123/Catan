#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/CardIsPacket.h"

/*
* CardIdParser
* Interpreta secuencia de bytes en paquete de datos de Card iS
*/
class CardIdParser : public ParserFsm {
public:
	/* Eventos del parser */
	enum Events : EventType { HEADER, RESOURCE, OTHER };

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class ResourceEvent : public Event {
	public:
		ResourceEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::RESOURCE; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType { HEAD, CARD };

	/*
	* generateEvent
	* Genera un evento a partir de un byte que interpreta para el parser
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	CardIsParser(void) : ParserFsm(&fsmTable[0][0], 2, 3, States::HEAD), packet(nullptr) {}

private:
	CardIsPacket * packet;

	const FsmCell fsmTable[2][3] = {
		//					HEADER									 RESOURCE										 OTHER
		{ { States::CARD, TX(RobberMoveParser, init) },{ States::HEAD, TX(RobberMoveParser ,error) },{ States::HEAD, TX(RobberMoveParser ,error) } }, // HEADER STATE
		{ { States::HEAD, TX(RobberMoveParser ,error) },{ States::HEAD, TX(RobberMoveParser, done) },{ States::HEAD, TX(RobberMoveParser ,error) } }, // CARD STATE
	};
};