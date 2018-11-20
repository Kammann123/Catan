#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/NamePacket.h"

/*
* NameParser
* Clase que permite parsear un conjunto de bytes como
* un paquete de datos que contiene el nombre del usuario
*/
class NameParser : public GenericFsm {
public:

	/*
	* Events
	* Eventos con los cuales funciona la FSM
	*/
	enum Events : EventType { HEADER, NUMBER, LETTER, LAST_LETTER, OTHER };

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

	class LetterEvent : public Event {
	public:
		LetterEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LETTER; }
	};

	class LastLetterEvent : public Event {
	public:
		LastLetterEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_LETTER; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/*
	* States
	* Estados de la FSM
	*/
	enum States : StateType {HEAD, COUNT, NAME};

	/*
	* generateEvent
	* Metodo que permite interpretar un byte y generar un evento
	* segun el tipo de byte recibido, a fin de usar ese evento para 
	* ciclar o correr la fsm de NameParser
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion de la FSM
	*/
	void init(GenericEvent* event);
	void setContext(GenericEvent* event);
	void setName(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	NameParser(void) : GenericFsm(&fsmTable[0][0], 3, 5, States::HEAD) , count(0), packet(nullptr) {}

private:
	unsigned int count;
	NamePacket* packet;

	const FsmCell fsmTable[3][5] = {
		//				HEADER									NUMBER									LETTER									LAST_LETTER									OTHER
		{ {States::COUNT, TX(NameParser, init)}, {States::HEAD, TX(NameParser, error)}, {States::HEAD, TX(NameParser, error)}, {States::HEAD, TX(NameParser, error)}, {States::HEAD, TX(NameParser, error)} },	// HEADER STATE
		{ {States::HEAD, TX(NameParser, error)}, {States::NAME, TX(NameParser, setContext)}, { States::HEAD, TX(NameParser, error) }, { States::HEAD, TX(NameParser, error) }, { States::HEAD, TX(NameParser, error) } }, // COUNT STATE
		{ {States::HEAD, TX(NameParser, error)}, { States::HEAD, TX(NameParser, error) }, {States::NAME, TX(NameParser, setName)}, {States::HEAD, TX(NameParser, done)}, { States::HEAD, TX(NameParser, error) } }, // NAME STATE
	};
};