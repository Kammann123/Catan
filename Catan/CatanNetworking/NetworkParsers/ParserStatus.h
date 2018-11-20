#pragma once

#include "../../FSM/GenericEvent.h"
#include "../NetworkPackets/NetworkPacket.h"

#include <iostream>

using namespace std;

/*
* ParserStatus
* Se definen estados posibles que pueden contenerse
* como posibles eventos de respuesta de los parsers
* de los que hara uso el DataPackets.
*/
enum ParserStatus : EventType { DONE, ERROR };

/*
* Event
* Evento generico dentro de los parsers, con el byte y el tipo a modo 
* de clasificacion.
*/
class Event : public GenericEvent {
public:
	Event(unsigned char byte) { this->byte = byte; }
	unsigned char getData(void) { return this->byte; }
private:
	unsigned char byte;
};

/*
* ErrorEvent y DoneEvent
* Eventos de respuesta de las fsm parsers, con resultado o error en caso de haberlo.
*/
class ErrorEvent : public GenericEvent {
public:
	ErrorEvent(const char* _error) : GenericEvent(), error(_error) {}
	EventType getType(void) { return ParserStatus::ERROR; }
	string& getError(void) { return this->error; }
private:
	string error;
};

class DoneEvent : public GenericEvent {
public:
	DoneEvent(NetworkPacket* packet) : GenericEvent() { this->packet = packet; }
	EventType getType(void) { return ParserStatus::DONE; }
	NetworkPacket* getPacket(void) { return this->packet; }
private:
	NetworkPacket * packet;
};