#include "CatanGame.h"

#include "../CatanEvents/DicesEvent.h"
#include "../CatanEvents/BankEvent.h"
#include "../CatanEvents/BuildingEvent.h"
#include "../CatanEvents/RobberMoveEvent.h"
#include "../CatanEvents/RobberCardEvent.h"
#include "../CatanEvents/OfferEvent.h"
#include "../CatanEvents/CatanEvent.h"

CatanGame::
CatanGame() : localPlayer(PlayerId::PLAYER_ONE), remotePlayer(PlayerId::PLAYER_TWO) {

	/* Inicializacion */
	this->prevState = nullptr;
	this->state = nullptr; // PRIMER ESTADO!!
}

CatanGame::
~CatanGame() {

	/* Me fijo si destruyo buildings */
	for (Building* b : builtMap) {
		delete b;
	}

	/* Destruyo estados */
	if (state) {
		delete state;
	}
	if (prevState) {
		delete prevState;
	}

	/* Destruyo eventos */
	for (CatanEvent* ev : eventQueue) {
		delete ev;
	}
}

CatanStatus
CatanGame::handle(NetworkPacket* packet) {

	CatanEvent* newEvent = this->packetDispatcher(packet);

	this->handle(newEvent);
}

CatanStatus
CatanGame::handle(CatanEvent* event) {
	this->state->handle(event);
}

bool
CatanGame::hasEvents(void) const {
	return !(this->eventQueue.empty());
}

CatanEvent*
CatanGame::getNextEvent(void) {
	if (hasEvents()) {
		CatanEvent* event = this->eventQueue.front();
		this->eventQueue.pop_front();
		return event;
	}
	else {
		return nullptr;
	}
}

void
CatanGame::changeState(CatanState* newState) {

	/* Borro el previo */
	delete prevState;

	/* Guardo previo */
	prevState = state;

	/* Actualizo y cambio */
	state = newState;
}

CatanEvent*
CatanGame::packetDispatcher(NetworkPacket* packet) {

	CatanEvent* newEvent = nullptr;

	switch (packet->getHeader()) {
	case PacketHeader::DICES_ARE:
		newEvent = new DicesEvent((DicesPacket*)packet);
		break;
	case PacketHeader::BANK_TRADE:
		newEvent = new BankEvent((BankPacket*)packet);
		break;
	case PacketHeader::OFFER_TRADE:
		newEvent = new OfferEvent((OfferPacket*)packet);
		break;
	case PacketHeader::ROBBER_CARDS:
		newEvent = new RobberCardEvent((RobberCardPacket*)packet);
		break;
	case PacketHeader::ROBBER_MOVE:
		newEvent = new RobberMoveEvent((RobberMovePacket*)packet);
		break;
	case PacketHeader::SETTLEMENT: case PacketHeader::ROAD: case PacketHeader::CITY:
		newEvent = new BuildingEvent((BuildingPacket*)packet);
		break;
	default:
		newEvent = new CatanEvent(packet);
		break;
	}

	return newEvent;
}

void 
CatanGame::addNewEvent(NetworkPacket* packet) {
	CatanEvent* event = this->packetDispatcher(packet);

	this->addNewEvent(event);
}

void
CatanGame::addNewEvent(CatanEvent* event) {
	this->eventQueue.push_back(event);
}

Player&
CatanGame::getLocalPlayer(void)
{
	return localPlayer;
}

Player&
CatanGame::getRemotePlayer(void)
{
	return remotePlayer;
}

list<Building*>&
CatanGame::getBuiltMap(void)
{
	return builtMap;
}

map<unsigned char, ResourceHex>
CatanGame::getResourceMap(void)
{
	return resourceMap;
}

map<unsigned char, SeaHex>
CatanGame::getSeaMap(void)
{
	return seaMap;
}

PlayerId
CatanGame::getTurn(void)
{
	return turn;
}

PlayerId
CatanGame::getLongestRoad(void)
{
	return longestRoad;
}

Robber
CatanGame::getRobber(void)
{
	return robber;
}

CatanState*
CatanGame::getCurrentState(void)
{
	return state;
}

CatanState*
CatanGame::getPrevState(void)
{
	return prevState;
}


