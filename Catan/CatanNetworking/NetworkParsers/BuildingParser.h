#pragma once

#include "ParserStatus.h"

#include "../../FSM/GenericFsm.h"

#include "../NetworkPackets/BuildingPacket.h"

/*
* BuildingParser
* Interpreta una secuencia de bytes que se toma como un paquete de datos que 
* representa la construccion de alguna de las entidades validas.
*/
class BuildingParser : public ParserFsm {
public:
	/* Eventos del parser */
	enum Events : EventType { HEADER, NUMBER, COORD, LAST_COORD, OTHER };

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

	class CoordEvent : public Event {
	public:
		CoordEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::COORD; }
	};

	class LastCoordEvent : public Event {
	public:
		LastCoordEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_COORD; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/* Estados del parser */
	enum States : StateType { HEAD, COUNT, COORDS };

	/*
	* generateEvent
	* Genera un evento interpretando un byte para el parser
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion
	*/
	void init(GenericEvent* event);
	void setContext(GenericEvent* event);
	void setCoord(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	BuildingParser(void) : ParserFsm(&fsmTable[0][0], 3, 5, States::HEAD), count(0), packet(nullptr) {}

private:
	unsigned int count;
	BuildingPacket * packet;

	const FsmCell fsmTable[3][5] = {
		//				HEADER									NUMBER										 COORD										LAST_COORD										OTHER
		{ {States::COUNT, TX(BuildingParser, init)}, {States::HEAD, TX(BuildingParser, error)}, { States::HEAD, TX(BuildingParser, error) }, { States::HEAD, TX(BuildingParser, error) }, { States::HEAD, TX(BuildingParser, error) } }, // HEADER STATE
		{ { States::HEAD, TX(BuildingParser, error) }, {States::COORDS, TX(BuildingParser, setContext)}, { States::HEAD, TX(BuildingParser, error) }, { States::HEAD, TX(BuildingParser, error) }, { States::HEAD, TX(BuildingParser, error) } }, // COUNT STATE
		{ { States::HEAD, TX(BuildingParser, error) }, { States::HEAD, TX(BuildingParser, error) }, {States::COORDS, TX(BuildingParser, setCoord)}, {States::HEAD, TX(BuildingParser, done)}, { States::HEAD, TX(BuildingParser, error) } }  // COORDS STATE
	};
};