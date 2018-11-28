#include "Idle.h"

#include "../CatanNetworking.h"

#include "ListenBank.h"
#include "ListenBuilding.h"
#include "ListenDices.h"
#include "ListenEnd.h"
#include "ListenOffer.h"
#include "ListenQuit.h"
#include "NetError.h"
#include "TellBank.h"
#include "TellBuilding.h"
#include "TellDices.h"
#include "TellEnd.h"
#include "TellOffer.h"
#include "TellQuit.h"

#define allocate(_constructor, ...)	(HandshakingState*)new _constructor(__VA_ARGS__)

Idle::
Idle(CatanNetworking& _networking) : NetworkingState(_networking, CatanNetworking::States::IDLE) {
	
	/* 
	* Se abren y crean los listeners y tellers 
	* para responder a peticiones ya sea de salida o entrada
	* para intercambio de datos. Notese que manejar nuevos protocolos
	* es adherir nuevos Listen y Tell objects.
	*/
	handlers = {
		allocate(ListenBank, _networking),
		allocate(ListenBuilding, _networking),
		allocate(ListenDices, _networking),
		allocate(ListenEnd, _networking),
		allocate(ListenOffer, _networking),
		allocate(ListenQuit, _networking),
		allocate(TellBank, _networking),
		allocate(TellBuilding, _networking),
		allocate(TellDices, _networking),
		allocate(TellEnd, _networking),
		allocate(TellOffer, _networking),
		allocate(TellQuit, _networking)
	};
}

Idle::
~Idle(void) {
	for (HandshakingState* state : handlers) {
		if(state)
			delete state;
	}
}

void
Idle::context(void) {}

void 
Idle::run(void) {

	/* Busco el socket */
	NetworkSocket* socket = networking.getSocket();

	/* Reviso mensajes */
	if (socket->hasReceived()){

		/* Ojeo el paquete que llego */
		NetworkPacket* packet = socket->look();

		/* Verifico si se puede hacer un dispatch */
		for (HandshakingState* state : handlers) {

			/* Verifico que el handler sea listener o both */
			if (state->isHeader(packet->getHeader(), ProtocolState::ProtocolType::LISTENER) || state->isHeader(packet->getHeader(), ProtocolState::ProtocolType::BOTH)) {

				/* Paso a ese estado! */
				networking.changeState(state);
				networking.run();
				return;
				
			}
		}

		/* No detecto nada! Error :'( */
		networking.setError("Idle - Error de protocolo, no se reconoce la peticion.");
		networking.changeState(CatanNetworking::States::NET_ERROR);
	}
}

void
Idle::update(void) {

	/* Busco el evento */
	CatanEvent* event = networking.getGame().getNextEvent();
	NetworkPacket* packet = networking.getEventPacket(event);

	/* Veo si alguno puede manejar */
	for (HandshakingState* state : handlers) {

		/* Verifico que el handler sea teller o both */
		if (state->isHeader(packet->getHeader(), ProtocolState::ProtocolType::TELLER) || state->isHeader(packet->getHeader(), ProtocolState::ProtocolType::BOTH)) {

			/* Paso a ese estado! */
			networking.changeState(state);
			networking.update();
			return;
		}
	}

	/* No detecto nada! Error :'( */
	networking.setError("Idle - Error de protocolo, no se reconoce la peticion.");
	networking.changeState(CatanNetworking::States::NET_ERROR);
}