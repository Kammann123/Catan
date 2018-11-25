#include "HandshakingState.h"

#include "../CatanNetworking.h"

#include "Idle.h"
#include "NetError.h"

HandshakingState::
HandshakingState(Protocol* p, CatanNetworking& net) : NetworkingState(net), handshakingProtocol(p) {}

HandshakingState::
~HandshakingState() {
	if (handshakingProtocol) {
		delete handshakingProtocol;
	}
}

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
				networking.changeState(new Idle(networking));
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("HandshakingState - Hubo error en el protocolo.");
				networking.changeState(new NetError(networking));
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("HandshakingState - Hubo error de timeout en el protocolo.");
				networking.changeState(new NetError(networking));
				break;
		}
	}
}

void
HandshakingState::update() {

	/* Busco nuevos eventos */
	CatanEvent* event = networking.getGame().getNextEvent();
	NetworkPacket* packet = networking.getEventPacket(event);

	/* Ejecuto el protocolo con el evento */
	handshakingProtocol->send(packet);

	/* Verifico estado del protocolo */
	switch (handshakingProtocol->getStatus()) {
		case ProtocolStatus::DONE:
			networking.changeState(new Idle(networking));
			break;
		case ProtocolStatus::PROTOCOL_ERROR:
			networking.setError("HandshakingState - Hubo error en el protocolo.");
			networking.changeState(new NetError(networking));
			break;
		case ProtocolStatus::TIMEOUT:
			networking.setError("HandshakingState - Hubo error de timeout en el protocolo.");
			networking.changeState(new NetError(networking));
			break;
	}
}

string
HandshakingState::what(void) { return string("HANDSHAKING"); }