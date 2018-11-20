#pragma once

#include "../../FSM/GenericFsm.h"

#include "ParserStatus.h"

#include "../NetworkPackets/MapPacket.h"

/*
* MapParser
* Clase para interpretar una secuencia de bytes como un paquete de mapa
*/
class MapParser : public GenericFsm {
public:

	/*
	* Events
	* Eventos de la fsm map parser
	*/
	enum Events : EventType { HEADER, INDEX, LAST_INDEX, OTHER };

	class HeaderEvent : public Event {
	public:
		HeaderEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::HEADER; }
	};

	class IndexEvent : public Event {
	public:
		IndexEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::INDEX; }
	};

	class LastIndexEvent : public Event {
	public:
		LastIndexEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::LAST_INDEX; }
	};

	class OtherEvent : public Event {
	public:
		OtherEvent(unsigned char byte) : Event(byte) {}
		EventType getType(void) { return Events::OTHER; }
	};

	/*
	* Estados de la FSM
	*/
	enum States : StateType { HEAD, MAP };

	/*
	* generateEvent
	* Genera un evento del tipo valido para el parser a partir de un byte.
	*/
	GenericEvent* generateEvent(unsigned char byte);

	/*
	* Rutinas de accion de la FSM
	*/
	void init(GenericEvent* event);
	void saveMap(GenericEvent* event);
	void done(GenericEvent* event);
	void error(GenericEvent* event);

	MapParser() : GenericFsm(&fsmTable[0][0], 2, 4, States::HEAD), nextIndex('0'), packet(nullptr) {}

private:
	unsigned char nextIndex;
	MapPacket * packet;

	const FsmCell fsmTable[2][4] = {
		//			HEADER									INDEX								LAST_INDEX								 OTHER
		{ {States::MAP, TX(MapParser, init)}, {States::HEAD, TX(MapParser, error)}, { States::HEAD, TX(MapParser, error) }, { States::HEAD, TX(MapParser, error) } },	// HEADER STATE
		{ {States::HEAD, TX(MapParser, error)}, {States::MAP, TX(MapParser, saveMap)}, {States::HEAD, TX(MapParser, done)}, {States::HEAD, TX(MapParser, error)} }	// MAP STATE
	};
};