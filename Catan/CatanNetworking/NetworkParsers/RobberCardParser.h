#pragma once

#include "ParserStatus.h"

#include "../NetworkPackets/RobberCardPacket.h"

#include "../../FSM/GenericFsm.h"

/*
* RobberCardParser
* Interpreta una secuencia de bytes como el paquete de dato de RobberCard
*/
class RobberCardParser : public GenericFsm {
public:
	/* Eventos del parser */
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
	enum States : StateType {HEAD, COUNT, RESOURCES};

	/* 
	* generateEvent
	* Interpreta un byte como un tipo de evento para el parser
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setContext(GenericEvent* event);
	void setResource(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	RobberCardParser(void) : GenericFsm(&fsmTable[0][0], 3, 5, States::HEAD), count(0), packet(nullptr) {}

private:
	unsigned int count;
	RobberCardPacket* packet;

	const FsmCell fsmTable[3][5] = {
		//					HEADER								NUMBER												 RESOURCE								LAST_RESOURCE										OTHER
		{ {States::COUNT, TX(RobberCardParser, init)}, {States::HEAD, TX(RobberCardParser, error)}, { States::HEAD, TX(RobberCardParser, error) }, { States::HEAD, TX(RobberCardParser, error) }, { States::HEAD, TX(RobberCardParser, error) } },	// HEADER STATE
		{ { States::HEAD, TX(RobberCardParser, error) }, {States::RESOURCES, TX(RobberCardParser, setContext)}, { States::HEAD, TX(RobberCardParser, error) }, { States::HEAD, TX(RobberCardParser, error) }, { States::HEAD, TX(RobberCardParser, error) } },	// COUNT STATE
		{ { States::HEAD, TX(RobberCardParser, error) }, { States::HEAD, TX(RobberCardParser, error) }, {States::RESOURCES, TX(RobberCardParser, setResource)}, {States::HEAD, TX(RobberCardParser, done)}, { States::HEAD, TX(RobberCardParser, error) } }	// RESOURCE STATE
	};
};