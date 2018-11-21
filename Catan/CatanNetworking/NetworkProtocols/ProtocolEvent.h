#pragma once

#include "../../FSM/GenericEvent.h"
#include "../NetworkPackets/NetworkPacket.h"

/*
* ProtocolEvent
* Eventos de las fsm de protocolos de comunicacion
*/
class ProtocolEvent : public GenericEvent {
public:
	ProtocolEvent(NetworkPacket* packet);

private:
	NetworkPacket * packet;
};