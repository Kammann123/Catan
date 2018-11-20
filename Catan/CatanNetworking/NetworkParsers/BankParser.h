#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/BankPacket.h"

/*
* BankParser
* Interpreta secuencia de bytes para poder armar el paquete de datos
* de un intercambio con el banco
*/
class BankParser : public GenericFsm {

public:
	/* Estados del parser */
	enum Events : EventType {HEADER, NUMBER, RESOURCE, LAST_RESOURCE, OTHER};

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class NumberEvent : public Event {
	public:
		NumberEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::NUMBER; }
	};

	class ResourceEvent : public Event {
	public:
		ResourceEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::RESOURCE; }
	};

	class LastResourceEvent : public Event {
	public:
		LastResourceEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_RESOURCE; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType {HEAD, COUNT, GIVEN, RECEIVED};

	/*
	* generateEvent
	* Genera el evento a partir del byte interpretandolo para el parser actual.
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setContext(GenericEvent* event);
	void setGiven(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	BankParser(void) : GenericFsm(&fsmTable[0][0], 4, 5, States::HEAD), count(0), packet(nullptr) {}

private:
	unsigned int count;
	BankPacket * packet;

	const FsmCell fsmTable[4][5] = {
		// HEADER NUMBER RESOURCE LAST_RESOURCE OTHER
		{ {States::COUNT, TX(BankParser,init)}, { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) }, {States::HEAD, TX(BankParser, error)} }, // HEADER STATE
		{ { States::HEAD, TX(BankParser, error) }, {States::GIVEN, TX(BankParser, setContext)}, { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) } }, // COUNT STATE
		{ { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) }, {States::GIVEN, TX(BankParser, setGiven)}, {States::RECEIVED, TX(BankParser, setGiven)}, { States::HEAD, TX(BankParser, error) } }, // GIVEN RESOURCE STATE
		{ { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) }, {States::HEAD, TX(BankParser, done)}, { States::HEAD, TX(BankParser, error) }, { States::HEAD, TX(BankParser, error) } }  // RECEIVED RESOURCE STATE
	};
};