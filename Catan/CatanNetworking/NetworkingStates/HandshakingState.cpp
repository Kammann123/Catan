#include "HandshakingState.h"

#include "../CatanNetworking.h"

#include "Idle.h"
#include "NetError.h"

HandshakingState::
HandshakingState(Protocol* p, CatanNetworking& net, unsigned int id) : NetworkingState(net, id), handshakingProtocol(p) {}

HandshakingState::
~HandshakingState() {
	if (handshakingProtocol) {
		delete handshakingProtocol;
	}
}

void
HandshakingState::context() {}

void
HandshakingState::run() {

	/* Busco el socket de networking */
	NetworkSocket* socket = networking.getSocket();

	/* Veo si hay mensajes */
	if (socket->hasReceived()) {

		/* Recibo mensaje y corro protocolo */
		NetworkPacket* packet = socket->receive();
		handshakingProtocol->recv(packet);

		/* Verifico estado de protocolo */
		switch (handshakingProtocol->getStatus()) {
			case ProtocolStatus::DONE:
				this->handshakingProtocol->reset();
				networking.changeState(CatanNetworking::States::IDLE);
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("HandshakingState - Hubo error en el protocolo.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("HandshakingState - Hubo error de timeout en el protocolo.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
		}
	}
}

void
HandshakingState::update() {

	/* Busco nuevos eventos */
	CatanEvent* event = networking.getGame().getNextEvent();
	NetworkPacket* packet = networking.getEventPacket(event);

	/* Resulta que hay eventos que no son interesantes para networking */
	if (packet) {

		/* Ejecuto el protocolo con el evento */
		handshakingProtocol->send(packet);

		/* Verifico estado del protocolo */
		switch (handshakingProtocol->getStatus()) {
			case ProtocolStatus::DONE:
				this->handshakingProtocol->reset();
				networking.changeState(CatanNetworking::States::IDLE);
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("HandshakingState - Hubo error en el protocolo.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("HandshakingState - Hubo error de timeout en el protocolo.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
		}
	}
}