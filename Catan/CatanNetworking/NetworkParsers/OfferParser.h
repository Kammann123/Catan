#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/OfferPacket.h"

/*
* OfferParser
* Interpreta secuencia de bytes como un paquete de intercambio de cartas
*/
class OfferParser : public ParserFsm {
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
	enum States : StateType {HEAD, GIVEN_COUNT, RECV_COUNT, GIVEN, RECV};

	/*
	* generateEvent
	* Genera el evento del parser a partir del byte dado
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/* Rutinas de accion */
	void init(GenericEvent* event);
	void setGivenCount(GenericEvent* event);
	void setRecvCount(GenericEvent* event);
	void setGiven(GenericEvent* event);
	void setRecv(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	OfferParser(void) : ParserFsm(&fsmTable[0][0], 5, 5, States::HEAD), givenCount(0), recvCount(0), packet(nullptr) {}

private:
	unsigned int givenCount;
	unsigned int recvCount;
	OfferPacket* packet;

	const FsmCell fsmTable[5][5] = {
		// HEADER NUMBER RESOURCE LAST_RESOURCE OTHER
		{ {States::GIVEN_COUNT, TX(OfferParser, init)},{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{States::HEAD, TX(OfferParser, error)} }, // HEADER STATE
		{ { States::HEAD, TX(OfferParser, error) },{States::RECV_COUNT, TX(OfferParser, setGivenCount)},{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) } }, // GIVEN COUNT STATE
		{ { States::HEAD, TX(OfferParser, error) },{States::GIVEN, TX(OfferParser, setRecvCount)},{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) } }, // RECV COUNT STATE
		{ { States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{States::GIVEN, TX(OfferParser, setGiven)},{States::RECV, TX(OfferParser, setGiven)},{ States::HEAD, TX(OfferParser, error) } }, // GIVEN STATE
		{ { States::HEAD, TX(OfferParser, error) },{ States::HEAD, TX(OfferParser, error) },{States::RECV, TX(OfferParser, setRecv)},{States::HEAD, TX(OfferParser, done)},{ States::HEAD, TX(OfferParser, error) } }, // RECV STATE
	};
};