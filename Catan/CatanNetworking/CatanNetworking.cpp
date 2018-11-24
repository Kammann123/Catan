#include "CatanNetworking.h"

#include "../CatanNetworking/NetworkPackets/BankPacket.h"
#include "../CatanNetworking/NetworkPackets/BuildingPacket.h"
#include "../CatanNetworking/NetworkPackets/CardIsPacket.h"
#include "../CatanNetworking/NetworkPackets/DicesPacket.h"
#include "../CatanNetworking/NetworkPackets/KnightPacket.h"
#include "../CatanNetworking/NetworkPackets/MonopolyPacket.h"
#include "../CatanNetworking/NetworkPackets/OfferPacket.h"
#include "../CatanNetworking/NetworkPackets/RobberCardPacket.h"
#include "../CatanNetworking/NetworkPackets/RobberMovePacket.h"
#include "../CatanNetworking/NetworkPackets/YOPPacket.h"
#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"
#include "../CatanEvents/BankEvent.h"
#include "../CatanEvents/BuildingEvent.h"
#include "../CatanEvents/CardIsEvent.h"
#include "../CatanEvents/DicesEvent.h"
#include "../CatanEvents/KnightEvent.h"
#include "../CatanEvents/MonopolyEvent.h"
#include "../CatanEvents/OfferEvent.h"
#include "../CatanEvents/RobberCardEvent.h"
#include "../CatanEvents/RobberMoveEvent.h"
#include "../CatanEvents/YOPEvent.h"
#include "../CatanEvents/CatanEvent.h"


#include <exception>

CatanNetworking::
CatanNetworking(string ip, unsigned int port, CatanGame& _game) : Observer(), game(_game){
	this->ip = ip;
	this->port = port;
	this->socket = nullptr;
	this->status = false;
	this->error = "";
	this->prevState = nullptr;
	this->currState = nullptr;
}

CatanNetworking::
~CatanNetworking(void) {
	if (socket)
		delete socket;
	if (this->currState)
		delete this->currState;
	if (this->prevState)
		delete this->prevState;
}

unsigned int 
CatanNetworking::getPort(void) {
	return port;
}

string 
CatanNetworking::getIp(void) {
	return ip;
}

NetworkSocket*
CatanNetworking::getSocket() {
	return socket;
}

void
CatanNetworking::setSocket(NetworkSocket* socket) {
	this->socket = socket;
}

CatanGame& 
CatanNetworking::getGame(void) {
	return this->game;
}

NetworkingState*
CatanNetworking::getState(void) {
	return currState;
}

string
CatanNetworking::getError(void) {
	return error;
}

bool
CatanNetworking::good(void) {
	return status;
}

void
CatanNetworking::setError(string msg) {
	this->status = false;
	this->error = msg;
}

void
CatanNetworking::setError(const char* msg) {
	this->status = false;
	this->error = msg;
}

void
CatanNetworking::verifyStatus(void) const {
	if (!status) {
		throw exception("Networking - verifyStatus - Hubo un error en el estado de Networking, revisar!");
	}
}

void
CatanNetworking::changeState(NetworkingState* state) {
	delete prevState;
	prevState = currState;
	currState = state;
}

void
CatanNetworking::run() {
	
	/* Verifico estado del Networking */
	verifyStatus();

	/* Actualizo el socket */
	if (this->socket) {

		/* Si esta conectado */
		if (socket->isConnected()) {
			/* Corro las colas de emision y recepcion de Tcp */
			socket->run();

			/* Verifico estado del socket */
			if (!socket->good()) {
				setError(socket->getError());
			}
		}
	}

	/* Ejecuto el run del estado */
	this->currState->run();
}

void
CatanNetworking::update() {

	/* Verifico estado del Networking */
	verifyStatus();

	/* Hay algun evento? */
	if (game.hasEvents()) {

		/* Busco el evento del juego */
		CatanEvent* event = game.getNextEvent();

		/* Verifico que sea para mi, y no un echo! */
		if (event->getSource() != CatanEvent::Sources::NETWORKING) {

			/* Ejecuto tarea */
			this->currState->update();
		}
	}
}

NetworkPacket*
CatanNetworking::getEventPacket(CatanEvent* event) {

	NetworkPacket* packet = nullptr;

	/*
	switch (event->getEvent()) {
		case CatanEvent::Events::THROW_DICES:
			break;
		case CatanEvent::Events::ROBBER_CARDS:
			break;
		case CatanEvent::Events::ROBBER_MOVE:
			break;
		case CatanEvent::Events::BUILDING:
			break;
		case CatanEvent::Events::BANK_TRADE:
			break;
		case CatanEvent::Events::OFFER_TRADE:
			break;
		case CatanEvent::Events::PASS:
			break;
		case CatanEvent::Events::CARD_IS:
			break;
		case CatanEvent::Events::KNIGHT:
			break;
		case CatanEvent::Events::MONOPOLY:
			break;
		case CatanEvent::Events::YOP:
			break;
		case CatanEvent::Events::DEV_CARD:
			break;
	}*/

	return packet;
}