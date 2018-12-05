#include "HandshakingState.h"

#include "../CatanNetworking.h"

#include "Idle.h"
#include "NetError.h"

HandshakingState::
HandshakingState(CatanNetworking& net, unsigned int id) : NetworkingState(net, NETWORKING_TIMEOUT, id) {}

HandshakingState::
~HandshakingState() {
	if (handshakingProtocol) {
		delete handshakingProtocol;
	}
}

void
HandshakingState::setProtocol(Protocol* protocol) {
	this->handshakingProtocol = protocol;
}

Protocol*
HandshakingState::getProtocol(void) {
	return this->handshakingProtocol;
}

void
HandshakingState::context() { 
	/* Inicio el protocolo */
	handshakingProtocol->start();

	/* Mensaje */
	networking.setInfo("[Networking] - HandshakingState -> Iniciando protocolo de comunicacion.");
}

bool
HandshakingState::isHeader(PacketHeader header) {
	return this->handshakingProtocol->isHeader(header);
}

bool
HandshakingState::isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) {
	return this->handshakingProtocol->isHeader(header, asWhat);
}

void
HandshakingState::confirm(NetworkPacket* packet) {
	networking.getGame().confirm(PlayerId::PLAYER_TWO);
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
				this->handshakingProtocol->reset();
				networking.changeState(CatanNetworking::States::IDLE, "[Networking] - HandshakingState -> Protocolo terminado. Estado de comunicacion OK!");
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("[Networking] - HandshakingState -> Hubo un error en el protocolo de comunicacion.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("[Networking] - HandshakingState -> Tiempo de espera agotado!");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
		}
	}
	else {

		/* Verifico el timeout del protocolo */
		if (handshakingProtocol->getStatus() == ProtocolStatus::TIMEOUT) {
			networking.setError("[Networking] - HandshakingState -> Tiempo de espera agotado!");
			networking.changeState(CatanNetworking::States::NET_ERROR);
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
				networking.changeState(CatanNetworking::States::IDLE, "[Networking] - HandshakingState -> Protocolo terminado. Estado de comunicacion OK!");
				break;
			case ProtocolStatus::PROTOCOL_ERROR:
				networking.setError("[Networking] - HandshakingState -> Hubo un error en el protocolo de comunicacion.");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
			case ProtocolStatus::TIMEOUT:
				networking.setError("[Networking] - HandshakingState -> Tiempo de espera agotado!");
				networking.changeState(CatanNetworking::States::NET_ERROR);
				break;
		}
	}
}