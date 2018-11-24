#include "CatanGame.h"

#include "../CatanEvents/DicesEvent.h"
#include "../CatanEvents/BankEvent.h"
#include "../CatanEvents/BuildingEvent.h"
#include "../CatanEvents/RobberMoveEvent.h"
#include "../CatanEvents/RobberCardEvent.h"
#include "../CatanEvents/OfferEvent.h"
#include "../CatanEvents/CatanEvent.h"

CatanGame::
CatanGame(string localPlayerName) : localPlayer(PlayerId::PLAYER_ONE), remotePlayer(PlayerId::PLAYER_TWO) {

	/* Inicializacion */
	this->prevState = nullptr;
	this->state = nullptr; // PRIMER ESTADO!!

	/* El nombre del jugador local */
	this->localPlayer.setName(localPlayerName);
}

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

	return this->handle(newEvent);
}

CatanStatus
CatanGame::handle(CatanEvent* event) {
	return this->state->handle(event);
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

//bool CatanGame::
//isValidDockTransaction(list<ResourceCard*>& offeredCards, ResourceId requestedCard, unsigned char seaCoord, unsigned char dockNumber, PlayerId player)
//{
//	// Busco las coordenadas del dock (?) -> tiene 2 !!!!! (cambiar el método)
//	SeaHex& mySeaHex = seaMap[seaCoord];
//	string dockCoords = seaMap[seaCoord].getDockAbsCoords(dockNumber);
//	// si es así, tendría que chequear si la oferta del jugador se condice con lo requerido por el puerto
//	//
//}

bool CatanGame::
isValidPlayerTransaction(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) 
{
	bool ret = false;
	PlayerId destPlayerID = ((srcPlayerID == PlayerId::PLAYER_ONE) ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE);

	if (isValidListOfCards(offeredCards, srcPlayerID) && isValidListOfCards(requestedCards, destPlayerID))
	{
		ret = true;
	}

	return ret;
}

bool CatanGame::
isValidBankTransaction(list<ResourceId>& offeredCards, PlayerId playerID)
{
	bool ret = false;

	if ((offeredCards.size() == BANK_TRANSACTION_CARDS_COUNT) && isValidListOfCards(offeredCards, playerID))
	{
		ret = true;
	}

	return ret;
}

bool CatanGame::
isValidListOfCards(list<ResourceId>& offeredCards, PlayerId playerID) 
{
	bool ret = false;
	Player& player = ((playerID == PlayerId::PLAYER_ONE) ? localPlayer : remotePlayer); 

	if (
		(getResourceCount(player.getResourceCards(), ResourceId::FOREST) >= getResourceCount(offeredCards, ResourceId::FOREST)) &&
		(getResourceCount(player.getResourceCards(), ResourceId::HILL) >= getResourceCount(offeredCards, ResourceId::HILL)) &&
		(getResourceCount(player.getResourceCards(), ResourceId::MOUNTAIN) >= getResourceCount(offeredCards, ResourceId::MOUNTAIN)) &&
		(getResourceCount(player.getResourceCards(), ResourceId::FIELD) >= getResourceCount(offeredCards, ResourceId::FIELD)) &&
		(getResourceCount(player.getResourceCards(), ResourceId::PASTURES) >= getResourceCount(offeredCards, ResourceId::PASTURES))
		)
	{
		ret = true; // Verifico si las cartas están disponibles
	}

	return ret;
}

unsigned int CatanGame::
getResourceCount(list<ResourceId>& cardsList, ResourceId resourceID) const
{
	unsigned int resourceCount = 0;
	for (ResourceId resID : cardsList) // range-based for de la lista de cartas de recursos
	{
		if (resID == resourceID) // verifico que el recurso sea el correcto
		{
			resourceCount++; // si es así, incremento el contador
		}
	}
	return resourceCount;
}

unsigned int CatanGame::
getResourceCount(list<ResourceCard*>& cardsList, ResourceId resourceID) const
{
	unsigned int resourceCount = 0;
	for (ResourceCard* resCard : cardsList) // range-based for de la lista de cartas de recursos
	{
		if (resCard->getResourceId() == resourceID) // verifico que el recurso sea el correcto
		{
			resourceCount++; // si es así, incremento el contador
		}
	}
	return resourceCount;
}

bool CatanGame::
hasRobberCards(PlayerId playerID)
{
	bool ret = false;
	Player& player = (playerID == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer);

	if (player.getResourceCards().size() > ROBBER_CARDS_COUNT)
	{
		ret = true;
	}

	return ret;
}

bool CatanGame::
isValidCity(string coords, PlayerId playerID) 
{
	bool ret = false;
	list<Building*>& buildings = this->getBuiltMap();

	for (Building* oneBuilding : buildings)
	{
		if (

			(oneBuilding->getType == BuildingType::SETTLEMENT) &&  // la construcción es un Settlement
			(oneBuilding->getPlayer() == playerID) &&              // es del jugador en cuestión
			matchCoords(oneBuilding->getPlace(), coords) &&
			// validar que la lista de cities tenga size > 0, 
			// validar recursos

			) 
		{
			ret = true;
			break; // para optimizar tiempo y no poner múltiples puntos de retorno
		}
	}

	return ret;

}

bool CatanGame::
hasRoadResources(PlayerId playerID)
{
	Player& player = (playerID == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer);
	bool ret = false;

	if ( 
		(getResourceCount(player.getResourceCards(), ResourceId::HILL) >= ROAD_BRICK_NEEDED ) &&
		(getResourceCount(player.getResourceCards, ResourceId::FOREST) >= ROAD_LUMBER_NEEDED )
		)
	{
		ret = true;
	}

	return ret;
}

bool CatanGame::
hasCityResources(PlayerId playerID)
{
	Player& player = (playerID == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer);
	bool ret = false;

	if (
		(getResourceCount(player.getResourceCards(), ResourceId::MOUNTAIN) >= CITY_ORE_NEEDED) &&
		(getResourceCount(player.getResourceCards, ResourceId::FIELD) >= CITY_GRAIN_NEEDED)
		)
	{
		ret = true;
	}

	return ret;
}


bool CatanGame::
hasSettlementResources(PlayerId playerID)
{
	Player& player = (playerID == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer);
	bool ret = false;

	if (
		(getResourceCount(player.getResourceCards(), ResourceId::HILL) >= SETTLEMENT_BRICK_NEEDED) &&
		(getResourceCount(player.getResourceCards, ResourceId::FIELD) >= SETTLEMENT_GRAIN_NEEDED) &&
		(getResourceCount(player.getResourceCards, ResourceId::FOREST) >= SETTLEMENT_LUMBER_NEEDED) &&
		(getResourceCount(player.getResourceCards, ResourceId::PASTURES) >= SETTLEMENT_WOOL_NEEDED)
		)
	{
		ret = true;
	}

	return ret;
}
bool CatanGame::
matchCoords(string str1, string str2)
{
	bool ret = true;

	if (str1.length() == str2.length()) // ambos strings deben tener la misma longitud
	{
		for (int i = 0 ; i < str1.length() ; i++) // para cada caracter del string1
		{
			if ( str2.find(str1.c_str()[i]) == string::npos ) // si no lo encuentro, entonces las coordenadas no son iguales
			{
				ret = false; // cambio el parámetro de return
				break; // y finalizo el barrido, porque ya las coordenadas no son iguales

			}
		}

	}

	else
	{
		ret = false;
	}

	return ret;
}

void CatanGame::
pass(void)
{
	this->turn = (this->turn == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE);
}
