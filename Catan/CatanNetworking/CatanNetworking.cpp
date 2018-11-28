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

#include "NetworkingStates/Disconnected.h"
#include "NetworkingStates/Listening.h"
#include "NetworkingStates/WaitSync.h"
#include "NetworkingStates/Sync.h"
#include "NetworkingStates/Idle.h"
#include "NetworkingStates/NetError.h"

#include <exception>

#define allocate(_key, _constr, ...) {_key, (NetworkingState*)new _constr(__VA_ARGS__)}

const char*
CatanNetworking::StateString[18] = {
	"DISCONNECTED", "LISTENING", "WAIT_SYNC", "SYNC", "IDLE", "NET_ERROR",
	"LISTEN_BANK", "LISTEN_BUILDING", "LISTEN_DICES", "LISTEN_END", "LISTEN_OFFER",
	"LISTEN_QUIT", "TELL_BANK", "TELL_BUILDING", "TELL_DICES", "TELL_END", "TELL_OFFER", "TELL_QUIT"
};

CatanNetworking::
CatanNetworking(string ip, unsigned int port, CatanGame& _game) : Observer(), game(_game){
	/* Inicializacion */
	this->ip = ip;
	this->port = port;
	this->socket = nullptr;
	this->status = true;
	this->error = "";

	/* Creo todos los estados */
	states.clear();
	states = {
		allocate(States::DISCONNECTED, Disconnected, *this),
		allocate(States::LISTENING, Listening, *this),
		allocate(States::IDLE, Idle, *this),
		allocate(States::WAIT_SYNC, WaitSync, *this),
		allocate(States::SYNC, Sync, *this),
		allocate(States::NET_ERROR, NetError, *this)
	};

	/* Estado inicial */
	changeState(States::DISCONNECTED);
}

CatanNetworking::
~CatanNetworking(void) {
	if (socket)
		delete socket;
	for (auto state : states) {
		if (state.second) {
			delete state.second;
		}
	}
}

CatanNetworking::States 
CatanNetworking::getNetworkingState(void) {
	return (CatanNetworking::States )this->currState->getId();
}

const char*
CatanNetworking::getNetworkingString(void) {
	return StateString[this->currState->getId()];
}

unsigned int 
CatanNetworking::getPort(void) {
	return port;
}

string 
CatanNetworking::getIp(void) {
	return ip;
}

NetworkSocket*&
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
CatanNetworking::changeState(CatanNetworking::States state) {
	changeState(states[state]);
}

void
CatanNetworking::changeState(NetworkingState* state) {
	currState = state;
	currState->context();
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
	if( this->good() )
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

			/*
			* Surgieron o puede surgir, eventos que sean de interes para otras partes del programa
			* pero no asi para el Networking, con lo cual, se presupone que los deberia ignorar el programa
			*/
			this->currState->update();
		}
	}
}

NetworkPacket*
CatanNetworking::getEventPacket(CatanEvent* event) {

	/*
	* Para NO PERDERSER... recordar lo siguiente respecto de este metodo.
	* Este METODO representa todos aquellos eventos de CatanGame, que le son
	* de interes al networking para poder correr sus protocolos, ninguna otra cosa debe
	* parsearse, y cualquier cosa que falte, hara inutil el protocolo.
	*
	* Reitero. Conversion de los eventos de CATAN que al networking le son de INTERES
	* en paquete de datos para transmitirlos!
	*/

	switch (event->getEvent()) {
		case CatanEvent::Events::THROW_DICES:
			return new DicesPacket(*((DicesEvent*)event));
			break;
		case CatanEvent::Events::ROBBER_CARDS:
			return new RobberCardPacket(*((RobberCardEvent*)event));
			break;
		case CatanEvent::Events::ROBBER_MOVE:
			return new RobberMovePacket(*((RobberMoveEvent*)event));
			break;
		case CatanEvent::Events::BUILDING:
			return new BuildingPacket(*((BuildingEvent*)event));
			break;
		case CatanEvent::Events::BANK_TRADE:
			return new BankPacket(*((BankEvent*)event));
			break;
		case CatanEvent::Events::OFFER_TRADE:
			return new OfferPacket(*((OfferEvent*)event));
			break;
		case CatanEvent::Events::CARD_IS:
			return new CardIsPacket(*((CardIsEvent*)event));
			break;
		case CatanEvent::Events::KNIGHT:
			return new KnightPacket(*((KnightEvent*)event));
			break;
		case CatanEvent::Events::MONOPOLY:
			return new MonopolyPacket(*((MonopolyEvent*)event));
			break;
		case CatanEvent::Events::YOP:
			return new YOPPacket(*((YOPEvent*)event));
			break;
		case CatanEvent::Events::DEV_CARD:
			return new NetworkPacket(PacketHeader::DEV_CARD);
			break;
		case CatanEvent::Events::PASS:
			return new NetworkPacket(PacketHeader::PASS);
			break;
		case CatanEvent::Events::QUIT:
			return new NetworkPacket(PacketHeader::QUIT);
			break;
		case CatanEvent::Events::ERROR_EVENT:
			return new NetworkPacket(PacketHeader::HEADER_ERROR);
			break;
		case CatanEvent::Events::PLAY_AGAIN:
			return new NetworkPacket(PacketHeader::PLAY_AGAIN);
			break;
		case CatanEvent::Events::GAME_OVER:
			return new NetworkPacket(PacketHeader::GAME_OVER);
			break;
		case CatanEvent::Events::WON:
			return new NetworkPacket(PacketHeader::I_WON);
			break;
		case CatanEvent::Events::YES:
			return new NetworkPacket(PacketHeader::YES);
			break;
		case CatanEvent::Events::NO:
			return new NetworkPacket(PacketHeader::NO);
			break;
		case CatanEvent::Events::ROAD_BUILDING:
			return new NetworkPacket(PacketHeader::ROAD_BUILDING);
			break;
	}

	return nullptr;
}