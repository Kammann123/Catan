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

#define RANDOM_DICE	((rand() % 6) + 1)

void
CatanGame::_init_game(void) {

	/* Inicializacion de variables */
	this->prevState = nullptr;
	this->state = nullptr;

	/* Semilla para numeros aleatorios */
	srand( (unsigned int)time(NULL) );
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

void
CatanGame::handle(NetworkPacket* packet) {

	CatanEvent* newEvent = this->getPacketEvent(packet);
	this->handle(newEvent);
}

void
CatanGame::handle(CatanEvent* event) {
	this->state->handle(event);
	delete event;
}

bool
CatanGame::hasEvents(void) const {
	return !(this->eventQueue.empty());
}

void
CatanGame::_notify_change(void) {

	/* Notifico a los observers */
	notifyObservers();

	/* Elimino el ultimo evento leido */
	if (hasEvents()) {
		CatanEvent* event = this->eventQueue.front();
		this->eventQueue.pop_front();
		delete event;
	}
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

map<Coord, MapValue>
CatanGame::getMap() {
	map<Coord, MapValue> gameMap;

	/* En el mapa del juego busco los hexagonos */
	for (auto hex : resourceMap) {
		/* Agrego al gameMap, los recursos id nomas */
		gameMap[hex.first] = (MapValue)hex.second.getResource();
	}

	return gameMap;
}

map<Coord, unsigned char>
CatanGame::getTokens() {
	map<Coord, unsigned char> tokenMap;

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
	for (unsigned int ii = 0; ii < 5; ii++) {

		unsigned int hexCount;
		ResourceId hexId;

		/* Elijo que tipo de recurso asignar  */
		switch ( ii ) {
			case 0:
				hexCount = HILL_HEX_COUNT;
				hexId = ResourceId::HILL;
				break;
			case 1:
				hexCount = FOREST_HEX_COUNT;
				hexId = ResourceId::FOREST;
				break;
			case 2:
				hexCount = MOUNTAIN_HEX_COUNT;
				hexId = ResourceId::MOUNTAIN;
				break;
			case 3:
				hexCount = FIELD_HEX_COUNT;
				hexId = ResourceId::FIELD;
				break;
			case 4:
				hexCount = PASTURE_HEX_COUNT;
				hexId = ResourceId::PASTURES;
				break;
		}

		/* Ubicamos aleatoriamente */
		for (unsigned int i = 0; i < hexCount; i++) {
			ResourceHex hex = ResourceHex(hexId, coords.back());
			coords.pop_back();
			resourceMap.insert(pair<Coord, ResourceHex>(hex.getCoord(), hex));
		}
	}

	/* Ubicamos aleatoriamente desert */
	resourceMap.insert(pair<unsigned char, ResourceHex>(coords.back(), ResourceHex(ResourceId::DESERT, coords.back())));
}

void
CatanGame::generateTurn() {
	turn = rand() % 2 ? PlayerId::PLAYER_ONE : PlayerId::PLAYER_TWO;
}

void
CatanGame::generateOcean() {

	/* Coordenadas disponibles */
	vector<unsigned char> coords;
	for (unsigned char i = '0'; i <= '5'; i++) coords.push_back(i);
	random_shuffle(coords.begin(), coords.end());

	/* Creo los elementos de mar */
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::SHEEP))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::BRICK))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::WOOD))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::WHEAT))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::STONE))), coords.pop_back();
}

void
CatanGame::generateTokens() {
	vector<unsigned char> tokens;
	unsigned char token;

	/* Genero los numeros aleatorios */
	tokens.push_back(2), tokens.push_back(12);
	for (unsigned int i = 0; i < 16; i++) {
		do {
			token = RANDOM_DICE + RANDOM_DICE;
		} while ( token == 7 || token == 2 || token == 12 );
		tokens.push_back(token);
	}
	random_shuffle(tokens.begin(), tokens.end());

	/* Asigno los tokens */
	for (auto& hex : resourceMap) {
		ResourceHex& resourceHex = hex.second;
		if (resourceHex.getResource() != ResourceId::DESERT) {
			resourceHex.setToken( tokens.back() ), tokens.pop_back();
		}
	}
}

void
CatanGame::assignResources(unsigned int dices) {

	/* Identifico las coordenadas en las cuales el token coincide
	* con el valor dado de dices, para entregar ese recurso */
	list<ResourceHex> hits;
	for (auto hex : resourceMap) {
		ResourceHex resourceHex = hex.second;
		if (resourceHex.getToken() == dices) {
			hits.push_back(resourceHex);
		}
	}

	/* Reviso todas las construcciones realizadas por lo usuarios
	* que estan jugando, y las que sean settlement o city, verifico
	* si esta alrededor del hexagono donde cayo el token y por cada
	* aparicio reparto recursos */
	for (Building* building : builtMap) {
		if (building->getType() == BuildingType::ROAD)	continue;

		for (ResourceHex hex : hits) {
			if (building->getPlace().isVertexOf(hex.getCoord())) {
				assignResources(building->getPlayer(), hex.getResource(), building->getType() == BuildingType::CITY ? 2 : 1);
			}
		}
	}
}

void
CatanGame::assignResources(PlayerId player, ResourceId resource, unsigned int qty) {
	/*
	* Busco al jugador y luego creo la cantidad de cartas necesaria
	* y le entrego una por una todas las que piden que le asigne
	*/
	Player playerObject = getPlayer(player);

	while (qty) {
		playerObject.addResourceCard(new ResourceCard(player, resource));
		qty--;
	}
}

void
CatanGame::updateLongestRoad(void) {
	/*
	* Primero busco en las construcciones realizadas por cada jugador
	* los roads que tiene, contando aquellos caminos que formo y de ellos
	* extrayendo la cantidad mas alta, luego comparando entre ambos jugadores
	* se obtiene el que tiene el camino mas largo.
	*/

	/* 
	* Se compara con el estado actual de longest road para determinar si hubo algun cambio
	* en caso de haberlo, se actualiza como corresponde, agregando puntaje y quitandolo
	* a quienes es debido
	*/
}

void
CatanGame::getLongestRoad(PlayerId playerId, unsigned int length) {
	/*
	* Obtengo los datos del jugador dado, y busco entre sus construcciones,
	* los caminos enlazados, encontrando el de mayor longitud.
	*/
}

bool
CatanGame::hasRobberCards(PlayerId playerID) {
	return (getPlayer(playerID).getResourceCount() > ROBBER_CARDS_COUNT);
}

void
CatanGame::robberCards(list<ResourceCard*>& cards, PlayerId playerID) 
{
	Player player = getPlayer(playerID);

	for (ResourceCard* card : cards)
	{
		player.removeResourceCard(card);
		delete card;
	}
}

void
CatanGame::robberCards(list<ResourceId>& cards, PlayerId playerID) {
	Player player = getPlayer(playerID);

	for (ResourceId card : cards) {
		player.removeResourceCard(card);
	}
}

void
CatanGame::moveRobber(Coord newCoords) {
	robber.setCoord(newCoords);
}

bool
CatanGame::isValidRoad(Coord coords, PlayerId playerID) {
	return false;
}


bool
CatanGame::isValidCity(Coord coords, PlayerId playerID) {
	bool ret = false;

	for (Building* building : builtMap) // Busco que exista un Settlement en la posicion indicada
	{
		if (
			building->getPlayer() == playerID &&
			building->getPlace() == coords &&
			building->getType == BuildingType::SETTLEMENT
			)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

bool
CatanGame::isValidSettlement(Coord coords, PlayerId playerID) {
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
CatanGame::buildRoad(Coord coords, PlayerId playerID)
{
	Building* newRoad = getPlayer(playerID).popRoad(); // Obtengo objeto pre-creado
	newRoad->setPlace(coords); // Asigno las coordenadas
	newRoad->setPlayer(playerID); // Asigno el ID del jugador propietario
	builtMap.push_back(newRoad); // Push del objeto en el mapa de construcciones
	getPlayer(playerID).addPoints(ROAD_BUILT_POINTS); // Asigno vp correspondientes a la construcción
}

void
CatanGame::buildCity(Coord coords, PlayerId playerID)
{
	Building* newCity = getPlayer(playerID).popCity(); // Obtengo objeto pre-creado
	newCity->setPlace(coords); // Asigno las coordenadas
	newCity->setPlayer(playerID); // Asigno el ID del jugador propietario
	builtMap.push_back(newCity); // Push del objeto en el mapa de construcciones

	for(Building* building : builtMap)
	{
		if (building->getPlace() == coords)
		{
			getPlayer(playerID).giveBackBuilding(building->getType(), building); // Devuelvo el Settlement sobre el que se construyó la City
			break;
		}
	}

}

void
CatanGame::buildSettlement(Coord coords, PlayerId playerID)
{
	Building* newSettlement = getPlayer(playerID).popSettlement(); // Obtengo objeto pre-creado
	newSettlement->setPlace(coords); // Asigno las coordenadas
	newSettlement->setPlayer(playerID); // Asigno el ID del jugador propietario
	builtMap.push_back(newSettlement); // Push del objeto en el mapa de construcciones
	getPlayer(playerID).addPoints(SETTLEMENT_BUILT_POINTS); // Asigno vp correspondientes a la construcción
}

bool 
CatanGame::isValidDockExchange(list<ResourceCard*>& offeredCards, ResourceId requestedCard, Coord seaCoord, unsigned char dockNumber, PlayerId player) {

	return false;
}

bool
CatanGame::isValidPlayerExchange(list<ResourceCard*>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	return	(
			canPlayerAccept(offeredCards, srcPlayerID) && 
			canPlayerAccept(requestedCards, (srcPlayerID == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE) )
			);

}

bool 
CatanGame::isValidBankExchange(list<ResourceCard*>& offeredCards, PlayerId playerID) {

	return (offeredCards.size() == BANK_TRANSACTION_CARDS_COUNT && canPlayerAccept(offeredCards,playerID));
}

bool
CatanGame::isAvailableDock(SeaId dockID, PlayerId playerID) {

	return false;
}

bool
CatanGame::canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID)
{
	
	return	(
			(getPlayer(destPlayerID).getResourceCount(ResourceId::FOREST) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::FOREST)) &&
			(getPlayer(destPlayerID).getResourceCount(ResourceId::HILL) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::HILL)) &&
			(getPlayer(destPlayerID).getResourceCount(ResourceId::MOUNTAIN) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::MOUNTAIN)) &&
			(getPlayer(destPlayerID).getResourceCount(ResourceId::FIELD) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::FIELD)) &&
			(getPlayer(destPlayerID).getResourceCount(ResourceId::PASTURES) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::PASTURES))
			);
}

bool
CatanGame::canPlayerAccept(list<ResourceCard*> requestedCards, PlayerId destPlayerID)
{
	unsigned int woodCount = 0, brickCount = 0, oreCount = 0, wheatCount = 0, woolCount = 0; // Inicializo contadores

	for (ResourceCard* card : requestedCards)
	{
		switch (card->getResourceId())
		{
		case ResourceId::FOREST:
			woodCount++;
			break;

		case ResourceId::HILL:
			brickCount++;
			break;

		case ResourceId::MOUNTAIN:
			oreCount++;
			break;

		case ResourceId::FIELD:
			wheatCount++;
			break;

		case ResourceId::PASTURES:
			woolCount++;
			break;

		default:
			break;
		}

	}

	return (
		(getPlayer(destPlayerID).getResourceCount(ResourceId::FOREST) >= woodCount) &&
		(getPlayer(destPlayerID).getResourceCount(ResourceId::HILL) >= brickCount) &&
		(getPlayer(destPlayerID).getResourceCount(ResourceId::MOUNTAIN) >= oreCount) &&
		(getPlayer(destPlayerID).getResourceCount(ResourceId::FIELD) >= wheatCount) &&
		(getPlayer(destPlayerID).getResourceCount(ResourceId::PASTURES) >= woolCount)
		);

}

void
CatanGame::Exchange(list<ResourceCard*>& offered, ResourceId wanted, PlayerId playerID) 
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

	/* Creo una lista con todas las resource cards que transferiré del jugador destino al jugador fuente del intercambio */

	list<ResourceCard*> wantedList = getPlayer(oponent).giveResourceCard(ResourceId::FOREST, std::count(wanted.begin(), wanted.end(), ResourceId::FOREST));
	wantedList.merge(getPlayer(oponent).giveResourceCard(ResourceId::HILL, std::count(wanted.begin(), wanted.end(), ResourceId::HILL)));
	wantedList.merge(getPlayer(oponent).giveResourceCard(ResourceId::MOUNTAIN, std::count(wanted.begin(), wanted.end(), ResourceId::MOUNTAIN)));
	wantedList.merge(getPlayer(oponent).giveResourceCard(ResourceId::FIELD, std::count(wanted.begin(), wanted.end(), ResourceId::FIELD)));
	wantedList.merge(getPlayer(oponent).giveResourceCard(ResourceId::PASTURES, std::count(wanted.begin(), wanted.end(), ResourceId::PASTURES)));


	for (ResourceCard* cardWanted : wantedList) // intercambio destinationPlayer -> sourcePlayer
	{
		cardWanted->setPlayerId(srcPlayerID); // Cambio el ID de la carta al de su nuevo propietario
		getPlayer(srcPlayerID).addResourceCard(cardWanted); // Agrego las cartas al jugador fuente
		getPlayer(oponent).removeResourceCard(cardWanted); // Remuevo las cartas ofrecidas por jugador destino

	}

}

void
CatanGame::pass() {
	this->turn = (this->turn == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE);
}

