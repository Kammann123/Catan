#include "CatanGame.h"

#include "../CatanEvents/DicesEvent.h"
#include "../CatanEvents/BankEvent.h"
#include "../CatanEvents/BuildingEvent.h"
#include "../CatanEvents/RobberMoveEvent.h"
#include "../CatanEvents/RobberCardEvent.h"
#include "../CatanEvents/OfferEvent.h"
#include "../CatanEvents/CatanEvent.h"
#include "../CatanEvents/CardIsEvent.h"
#include "../CatanEvents/MonopolyEvent.h"
#include "../CatanEvents/YOPEvent.h"
#include "../CatanEvents/KnightEvent.h"

#include <algorithm>
#include <vector>
#include <time.h>

void
CatanGame::_init_game(void) {

	/* Inicializacion de variables */
	this->prevState = nullptr;
	this->state = nullptr;

	/* Semilla para numeros aleatorios */
	srand(time(NULL));
}

void
CatanGame::_free_buildings(void) {

	/* Me fijo si destruyo buildings */
	for (Building* b : builtMap) {
		delete b;
	}
}

void
CatanGame::_free_events(void) {

	/* Destruyo eventos */
	for (CatanEvent* ev : eventQueue) {
		delete ev;
	}
}

void
CatanGame::_free_states(void) {

	/* Destruyo estados */
	if (state) {
		delete state;
	}
	if (prevState) {
		delete prevState;
	}
}

void
CatanGame::_clear_resource_map(void) {
	resourceMap.clear();
}

void
CatanGame::_clear_sea_map(void) {
	seaMap.clear();
}

CatanGame::
CatanGame(string localPlayerName) : localPlayer(PlayerId::PLAYER_ONE), remotePlayer(PlayerId::PLAYER_TWO) {

	/* Inicializacion */
	_init_game();

	/* El nombre del jugador local */
	this->localPlayer.setName(localPlayerName);
}

CatanGame::
CatanGame() : localPlayer(PlayerId::PLAYER_ONE), remotePlayer(PlayerId::PLAYER_TWO) {

	/* Inicializacion */
	_init_game();
}

CatanGame::
~CatanGame() {
	_free_buildings();
	_free_events();
	_free_states();
}

CatanStatus
CatanGame::handle(NetworkPacket* packet) {

	CatanEvent* newEvent = this->getPacketEvent(packet);
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
CatanGame::getPacketEvent(NetworkPacket* packet) {

	/*
	* Para NO PERDERSE... es importante recordar que la utilidad de este metodo
	* es la de convertir los paquete de datos de networking que le son de INTERES,
	* al CatanGame para poder operar el juego. Por tanto, se listan aquellos
	* paquetes que son de interes, y solo estos. Ningun otro.
	*/

	switch (packet->getHeader()) {
		case PacketHeader::DICES_ARE:
			return new DicesEvent((DicesPacket*)packet);
			break;
		case PacketHeader::BANK_TRADE:
			return new BankEvent((BankPacket*)packet);
			break;
		case PacketHeader::OFFER_TRADE:
			return new OfferEvent((OfferPacket*)packet);
			break;
		case PacketHeader::ROBBER_CARDS:
			return new RobberCardEvent((RobberCardPacket*)packet);
			break;
		case PacketHeader::ROBBER_MOVE:
			return new RobberMoveEvent((RobberMovePacket*)packet);
			break;
		case PacketHeader::CARD_IS:
			return new CardIsEvent((CardIsPacket*)packet);
			break;
		case PacketHeader::MONOPOLY:
			return new MonopolyEvent((MonopolyPacket*)packet);
			break;
		case PacketHeader::YEARS_OF_PLENTY:
			return new YOPEvent((YOPPacket*)packet);
			break;
		case PacketHeader::KNIGHT:
			return new KnightEvent((KnightPacket*)packet);
			break;
		case PacketHeader::SETTLEMENT: case PacketHeader::ROAD: case PacketHeader::CITY:
			return new BuildingEvent((BuildingPacket*)packet);
			break;
		case PacketHeader::PASS:
			return new CatanEvent(CatanEvent::Events::PASS, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::QUIT:
			return new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::I_WON:
			return new CatanEvent(CatanEvent::Events::WON, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::GAME_OVER:
			return new CatanEvent(CatanEvent::Events::GAME_OVER, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::PLAY_AGAIN:
			return new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::DEV_CARD:
			return new CatanEvent(CatanEvent::Events::DEV_CARD, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::YES:
			return new CatanEvent(CatanEvent::Events::YES, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::NO:
			return new CatanEvent(CatanEvent::Events::NO, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
		case PacketHeader::ROAD_BUILDING:
			return new CatanEvent(CatanEvent::Events::ROAD_BUILDING, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO);
			break;
	}

	/*
	* El uso de esta excepcion busca romper con el flujo del programa si algun
	* paquete recibido desde CatanNetworking no es de interes como evento para CatanGame
	* en cuyo caso, es un error del programador y no une eventualidad a manejar en el flujo,
	* asi, se encuentra el error y se corrige mediante la excepcion.
	*/
	throw exception("CatanGame - Un paquete de networking no se pudo parsear en evento");
}

void 
CatanGame::addNewEvent(NetworkPacket* packet) {
	CatanEvent* event = this->getPacketEvent(packet);

	this->addNewEvent(event);
}

void
CatanGame::addNewEvent(CatanEvent* event) {
	this->eventQueue.push_back(event);
}

PlayerId
CatanGame::getTurn(void)
{
	return turn;
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

bool
CatanGame::isRobberStatus() {
	return false;

}

void
CatanGame::setRemoteName(string remoteName) {
	this->remotePlayer.setName(remoteName);
}

string
CatanGame::getLocalName() {
	return this->localPlayer.getName();
}

map<unsigned char, MapValue>
CatanGame::getMap() {
	map<unsigned char, MapValue> gameMap;

	/* En el mapa del juego busco los hexagonos */
	for (auto hex : resourceMap) {
		/* Agrego al gameMap, los recursos id nomas */
		gameMap[hex.first] = (MapValue)hex.second.getResource();
	}

	return gameMap;
}

map<unsigned char, unsigned char>
CatanGame::getTokens() {
	map<unsigned char, unsigned char> tokenMap;

	/* En el mapa del juego busco los hexagonos */
	for (auto hex : resourceMap) {
		/* Agrego al gameMap, los recursos id nomas */
		tokenMap[hex.first] = hex.second.getToken();
	}

	return tokenMap;
}

Player&
CatanGame::getPlayer(PlayerId playerId) {
	return playerId == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer;
}

void
CatanGame::resetGame() {

	/* Reinicio los estados de los jugadores */
	localPlayer.reset();
	remotePlayer.reset();

	/* Limpio los estados, construcciones y eventos */
	_free_buildings();
	_free_events();
	_free_states();

	/* Elimino los recursos y el agua como se despliegan */
	_clear_resource_map();
	_clear_sea_map();

	/* Inicializo el juego */
	_init_game();
}

void 
CatanGame::generateMap() {

	/* Creacion aleatoria de posiciones */
	vector<unsigned char> coords;
	for (unsigned char c = 'A'; c <= 'S'; c++)	coords.push_back(c);
	random_shuffle(coords.begin(), coords.end());

	/* Ubicamos aleatoriamente hill */
	for (unsigned int i = 0; i < HILL_HEX_COUNT; i++) {
		ResourceHex hex = ResourceHex(ResourceId::HILL, coords.back());
		coords.pop_back();
		resourceMap[hex.getCoord()] = hex;
	}

	/* Ubicamos aleatoriamente forest */

	/* Ubicamos aleatoriamente mountain */

	/* Ubicamos aleatoriamente field */

	/* Ubicamos aleatoriamente pasture */

	/* Ubicamos aleatoriamente desert */

}

void
CatanGame::generateTurn() {

}

void
CatanGame::generateOcean() {

}

void
CatanGame::generateTokens() {

}

void
CatanGame::assignResources(unsigned int dices) {

}

bool
CatanGame::hasRobberCards(PlayerId playerID) {
	return (getPlayer(playerID).getResourceCount() > ROBBER_CARDS_COUNT);
}

void
CatanGame::robberCards(list<ResourceCard*>& cards, PlayerId playerID) {

}

void
CatanGame::moveRobber(unsigned char newCoords) {
	robber.setCoord(newCoords);
}

bool
CatanGame::isValidRoad(string coords, PlayerId playerID) {
	return false;
}

bool
CatanGame::isValidCity(string coords, PlayerId playerID) {
	return false;
}

bool
CatanGame::isValidSettlement(string coords, PlayerId playerID) {
	return false;
}

bool
CatanGame::hasCityResources(PlayerId playerID) {
	Player player = getPlayer(playerID);

	return (
		player.getResourceCount(ResourceId::MOUNTAIN) >= CITY_ORE_NEEDED &&
		player.getResourceCount(ResourceId::FIELD) >= CITY_GRAIN_NEEDED
		);
}

bool 
CatanGame::hasSettlementResources(PlayerId playerID) {
	Player player = getPlayer(playerID);

	return(
		player.getResourceCount(ResourceId::HILL) >= SETTLEMENT_BRICK_NEEDED &&
		player.getResourceCount(ResourceId::FIELD) >= SETTLEMENT_GRAIN_NEEDED &&
		player.getResourceCount(ResourceId::FOREST) >= SETTLEMENT_LUMBER_NEEDED &&
		player.getResourceCount(ResourceId::PASTURES) >= SETTLEMENT_WOOL_NEEDED
		);
}

bool
CatanGame::hasRoadResources(PlayerId playerID) {
	Player player = getPlayer(playerID);

	return (
		player.getResourceCount(ResourceId::HILL) >= ROAD_BRICK_NEEDED &&
		player.getResourceCount(ResourceId::FOREST) >= ROAD_LUMBER_NEEDED
		);
}

void
CatanGame::buildRoad(string coords, PlayerId playerID) 
{
	Building* newRoad = getPlayer(playerID).popRoad(); // Obtengo objeto pre-creado
	newRoad->setPlace = coords; // Asigno las coordenadas
	newRoad->setPlayer = playerID; // Asigno el ID del jugador propietario
	builtMap.push_back(newRoad); // Push del objeto en el mapa de construcciones
	getPlayer(playerID).addPoints(ROAD_BUILT_POINTS); // Asigno vp correspondientes a la construcción
}

void
CatanGame::buildCity(string coords, PlayerId playerID)
{
	Building* newCity = getPlayer(playerID).popCity(); // Obtengo objeto pre-creado
	newCity->setPlace = coords; // Asigno las coordenadas
	newCity->setPlayer = playerID; // Asigno el ID del jugador propietario
	builtMap.push_back(newCity); // Push del objeto en el mapa de construcciones

	for(Building* building : builtMap)
	{
		if (matchCoords(building->getPlace(), coords))
		{
			getPlayer(playerID).giveBackBuilding(building->getType(), building); // Devuelvo el Settlement sobre el que se construyó la City
			break;
		}
	}

}

void
CatanGame::buildSettlement(string coords, PlayerId playerID) 
{
	Building* newSettlement = getPlayer(playerID).popSettlement(); // Obtengo objeto pre-creado
	newSettlement->setPlace = coords; // Asigno las coordenadas
	newSettlement->setPlayer = playerID; // Asigno el ID del jugador propietario
	builtMap.push_back(newSettlement); // Push del objeto en el mapa de construcciones
	getPlayer(playerID).addPoints(SETTLEMENT_BUILT_POINTS); // Asigno vp correspondientes a la construcción
}

bool 
CatanGame::isValidDockExchange(list<ResourceCard*>& offeredCards, ResourceId requestedCard, unsigned char seaCoord, unsigned char dockNumber, PlayerId player) {

	return false;
}

bool
CatanGame::isValidPlayerExchange(list<ResourceCard*>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	return false;

}

bool 
CatanGame::isValidBankExchange(list<ResourceCard*>& offeredCards, PlayerId playerID) {

	return false;
}

bool
CatanGame::isAvailableDock(SeaId dockID, PlayerId playerID) {

	return false;
}

bool
CatanGame::canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID) {
	
	bool ret = false;

	if (
		( getPlayer(destPlayerID).getResourceCount(ResourceId::FOREST) >= std::count(requestedCards.begin(),requestedCards.end(),ResourceId::FOREST) ) &&
		( getPlayer(destPlayerID).getResourceCount(ResourceId::HILL) >= std::count(requestedCards.begin(), requestedCards.end(), ResourceId::HILL) ) &&
		( getPlayer(destPlayerID).getResourceCount(ResourceId::MOUNTAIN) >= std::count(requestedCards.begin(), requestedCards.end(), ResourceId::MOUNTAIN) ) &&
		( getPlayer(destPlayerID).getResourceCount(ResourceId::FIELD) >= std::count(requestedCards.begin(), requestedCards.end(), ResourceId::FIELD) ) &&
		( getPlayer(destPlayerID).getResourceCount(ResourceId::PASTURES) >= std::count(requestedCards.begin(), requestedCards.end(), ResourceId::PASTURES) )
		)
	{
		ret = true; // Verifico si las cartas están disponibles
	}

	return ret;
}

void
CatanGame::bankExchange(list<ResourceCard*>& offered, ResourceId wanted, PlayerId playerID) 
{
	for (ResourceCard* cardOffered : offered)
	{
		getPlayer(playerID).removeResourceCard(cardOffered); // remuevo las cartas ofrecidas
	}

	ResourceCard* newCard = new ResourceCard(playerID,wanted); // Creo nuevo objeto ResourceCard
	getPlayer(playerID).addResourceCard(newCard); // Asigno la nueva carta al jugador
}

void
CatanGame::playerExchange(list<ResourceCard*>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID) 
{
	PlayerId oponent = (srcPlayerID == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE); // ID del jugador contrario

	for (ResourceCard* cardOffered : offered) // intercambio sourcePlayer -> destinationPlayer
	{
		cardOffered->setPlayerId(oponent); // Cambio el ID de la carta al de su nuevo propietario
		getPlayer(oponent).addResourceCard(cardOffered); // Agrego las cartas al jugador destino
		getPlayer(srcPlayerID).removeResourceCard(cardOffered); // Remuevo las cartas ofrecidas por jugador fuente
	}

	list<ResourceCard*> wantedList = getPlayer(oponent).giveResourceCard(ResourceId::FOREST, std::count(wanted.begin(), wanted.end(), ResourceId::FOREST)).merge(getPlayer(oponent).giveResourceCard(ResourceId::HILL, std::count(wanted.begin(), wanted.end(), ResourceId::HILL)).merge(getPlayer(oponent).giveResourceCard(ResourceId::MOUNTAIN, std::count(wanted.begin(), wanted.end(), ResourceId::MOUNTAIN)).merge(getPlayer(oponent).giveResourceCard(ResourceId::FIELD, std::count(wanted.begin(), wanted.end(), ResourceId::FIELD)).merge(getPlayer(oponent).giveResourceCard(ResourceId::PASTURES, std::count(wanted.begin(), wanted.end(), ResourceId::PASTURES))))));

	for (ResourceCard* cardWanted : wantedList) // intercambio destinationPlayer -> sourcePlayer
	{
		cardWanted->setPlayerId(srcPlayerID); // Cambio el ID de la carta al de su nuevo propietario
		getPlayer(srcPlayerID).addResourceCard(cardWanted); // Agrego las cartas al jugador fuente
		getPlayer(oponent).removeResourceCard(cardWanted); // Remuevo las cartas ofrecidas por jugador destino

	}

}

void
CatanGame::dockExchange(list<ResourceCard*>& offered, ResourceId wanted, PlayerId playerID) {

}

void
CatanGame::pass() {
	this->turn = (this->turn == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE);
}

bool CatanGame::
isValidCity(string coords, PlayerId playerID)
{
	bool ret = false;
	list<Building*>& buildings = this->builtMap;

	for (Building* oneBuilding : buildings)
	{
		if (

			(oneBuilding->getType == BuildingType::SETTLEMENT) &&  // la construcción es un Settlement
			(oneBuilding->getPlayer() == playerID) &&              // es del jugador en cuestión
			matchCoords(oneBuilding->getPlace(), coords)

			)
		{
			ret = true;
			break; // para optimizar tiempo y no poner múltiples puntos de retorno
		}
	}

	return ret;

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

/*
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

*/