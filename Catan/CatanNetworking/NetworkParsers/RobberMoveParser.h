#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/RobberMovePacket.h"

/*
* RobberMoveParser
* Interpreta secuencia de bytes en paquete de datos con movimiento del robber
*/
class RobberMoveParser : public ParserFsm {
public:
	/* Eventos del parser */
	enum Events : EventType {HEADER, POSITION, OTHER};

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class PositionEvent : public Event {
	public:
		PositionEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::POSITION; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType {HEAD, MOVE};

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

	RobberMoveParser(void) : ParserFsm(&fsmTable[0][0], 2, 3, States::HEAD), packet(nullptr) {}

private:
	RobberMovePacket * packet;

	const FsmCell fsmTable[2][3] = {
		//					HEADER									 POSITION										 OTHER
		{ {States::MOVE, TX(RobberMoveParser, init)}, {States::HEAD, TX(RobberMoveParser ,error)}, { States::HEAD, TX(RobberMoveParser ,error) } }, // HEADER STATE
 		{ { States::HEAD, TX(RobberMoveParser ,error) }, {States::HEAD, TX(RobberMoveParser, done)}, { States::HEAD, TX(RobberMoveParser ,error) } }, // MOVE STATE
	};
};