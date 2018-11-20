#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/DevCardPacket.h"

/*
* DevCardParser
* Interpreta secuencia de bytes y convierte a paquete de datos dado,
* avisando si es correcto o si hubo algun tipo de error.
*/
class DevCardParser : public GenericFsm {
public:

	/* Eventos del parser */
	enum Events : EventType {HEADER, CARD, LAST_CARD, OTHER};

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class CardEvent : public Event {
	public:
		CardEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::CARD;  }
	};

	class LastCardEvent : public Event {
	public:
		LastCardEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_CARD;  }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType {HEAD, CARDS};

	/* 
	* generateEvent
	* Interpreta un byte y lo traduce a un evento para la fsm del parser
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setCard(GenericEvent* event);
	void error(GenericEvent* event);
	void done(GenericEvent* event);

	DevCardParser(void) : GenericFsm(&fsmTable[0][0], 2, 4, States::HEAD), nextIndex(0), packet(nullptr) {}
private:
	unsigned char nextIndex;
	DevCardPacket* packet;

	const FsmCell fsmTable[2][4] = {
		//				HEADER									CARD									LAST_CARD									OTHER
		{ {States::CARDS, TX(DevCardParser, init)}, {States::HEAD, TX(DevCardParser, error)}, {States::HEAD, TX(DevCardParser, error)}, {States::HEAD, TX(DevCardParser, error)} }, // HEADER STATE
		{ { States::HEAD, TX(DevCardParser, error) }, { States::CARDS, TX(DevCardParser, setCard) }, { States::HEAD, TX(DevCardParser, done) }, { States::HEAD, TX(DevCardParser, error) } }  // CARDS STATE
	};
};