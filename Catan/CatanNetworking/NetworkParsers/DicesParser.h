#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/DicesPacket.h"

/*
* DicesParser
* Interpreta una secuencia de bytes y lo convierte al paquete de datos
*/
class DicesParser : public ParserFsm {
public:

	/* Eventos del parser */
	enum Events : EventType { HEADER, DICE, OTHER };

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class DiceEvent : public Event {
	public:
		DiceEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::DICE; }
	};

	class OtherEvent : public Event{
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER;  }
	};

	/* Estados del parser */
	enum States : StateType {HEAD, FIRST_DICE, SECOND_DICE};
	
	/*
	* generateEvent
	* Genera un evento para el parser a partir de un byte
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/* 
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setDice(GenericEvent* event);
	void error(GenericEvent* event);
	void done(GenericEvent* event);

	DicesParser(void) : ParserFsm(&fsmTable[0][0], 3, 3, States::HEAD), packet(nullptr) {}

private:
	DicesPacket * packet;

	const FsmCell fsmTable[3][3] = {
		// HEADER DICE OTHER
		{ {States::FIRST_DICE, TX(DicesParser, init)}, {States::HEAD, TX(DicesParser, error)}, { States::HEAD, TX(DicesParser, error) } },		// HEADER STATE
		{ { States::HEAD, TX(DicesParser, error) }, {States::SECOND_DICE, TX(DicesParser, setDice)}, { States::HEAD, TX(DicesParser, error) } },		// FIRST DICE STATE
		{ { States::HEAD, TX(DicesParser, error) }, {States::HEAD, TX(DicesParser, done)}, { States::HEAD, TX(DicesParser, error) } }		// SECOND DICE STATE
	};
};