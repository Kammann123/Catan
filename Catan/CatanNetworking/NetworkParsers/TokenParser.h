#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/TokenPacket.h"
/*
* TokenParser
* Interpreta una secuencia de bytes conviertiendola en el paquete de 
* informacion de tokens del mapa!
*/
class TokenParser : public ParserFsm {
public:
	/*
	* Eventos del parser
	*/
	enum Events : EventType { HEADER, TOKEN, LAST_TOKEN, OTHER };

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class TokenEvent : public Event {
	public:
		TokenEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::TOKEN; }
	};

	class LastTokenEvent : public Event {
	public:
		LastTokenEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_TOKEN; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/*
	* Estados del parser
	*/
	enum States : StateType { HEAD, MAP };

	/*
	* generateEvent
	* Generador de los eventos para el parser que solo interpreta el byte
	* y define el tipo de evento a tratar.
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setToken(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	TokenParser(void) : ParserFsm(&fsmTable[0][0], 2, 4, States::HEAD), nextIndex('A'), packet(nullptr) {}
private:
	unsigned char nextIndex;
	TokenPacket* packet;

	const FsmCell fsmTable[2][4] = {
		// HEADER TOKEN LAST_TOKEN OTHER
		{ {States::MAP, TX(TokenParser, init)}, {States::HEAD, TX(TokenParser, error)}, { States::HEAD, TX(TokenParser, error) }, { States::HEAD, TX(TokenParser, error) } },	// HEADER STATE
		{ {States::HEAD, TX(TokenParser, error)}, {States::MAP, TX(TokenParser, setToken)}, {States::HEAD, TX(TokenParser, done)}, {States::HEAD, TX(TokenParser, error)} }  // MAP STATE
	};
};