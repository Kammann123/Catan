#pragma once

#include "../../FSM/GenericEvent.h"
#include "../NetworkPackets/NetworkPacket.h"

/*
* ProtocolEvent
* Se definen evnetos de fsm para definir protocolos de comunicacion en base a los paquetes de datos
* recibidos por red, en la misma comunicacion, donde el ProtocolEvent puede ser en funcion de algun paquete,
* o se toma el PacketHeader::OTHER en aquellos paquetes que sean ignorados o tomados como error para algun protocolo.
*/
class ProtocolEvent : public GenericEvent {
public:
	/* Constructor del ProtocolEvent */
	ProtocolEvent(NetworkPacket* _packet) : GenericEvent(), packet(_packet), type(_packet->getHeader()) {}
	ProtocolEvent(void) : GenericEvent(), packet(nullptr), type(PacketHeader::OTHER) {}

	/*
	* getPacket
	* Devuelve el paquete de datos almacenado en el evento
	*/
	NetworkPacket * getPacket(void) { return this->packet; }

	EventType getType(void) { return type; }

private:
	NetworkPacket * packet;
	EventType type;
};