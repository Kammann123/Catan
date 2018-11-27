#include "CatanGame.h"

#include "../CatanEvents/KnightEvent.h"
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

#include "CatanStates/GameSync.h"
#include "CatanStates/GameEnd.h"

#include <algorithm>
#include <vector>
#include <time.h>

void
CatanGame::_init_game(void) {

	/* Inicializacion de variables */
	this->prevState = nullptr;
	this->state = new GameSync(*this);
	this->longestRoad = PlayerId::PLAYER_NONE;
	this->winner = PlayerId::PLAYER_NONE;
	this->turn = PlayerId::PLAYER_NONE;
	this->description = "";

	/* Limpio los diccionarios */
	builtMap.clear();
	resourceMap.clear();
	seaMap.clear();
	playerLongestRoad.clear();
	playerDocks.clear();

	/* Semilla para numeros aleatorios */
	srand( (unsigned int)time(NULL) );

	/* Los estados de longest road */
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_ONE, 0));
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_TWO, 0));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_ONE, {}));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_TWO, {}));
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

void
CatanGame::setInfo(string info) {
	this->description = info;
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

	/*
	* Valido que haya llegado verdaderamente un evento
	* y no algun tipo de puntero nulo por algun error...
	*/
	if (event) {

		/*
		* Valido que el evento particular no sea de cierre
		* en cuyo caso... adios!
		*/
		if (event->getEvent() == CatanEvent::Events::QUIT) {
			changeState(new GameEnd(*this), "CatanGame - El juego ha finalizado por cierre de alguna de las partes.");
		}
		else {

			this->state->handle(event);
		}
	}
}

CatanGame::State
CatanGame::getState(void) {
	return (State)this->state->getId();
}

string
CatanGame::info(void) {
	return description;
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
CatanGame::changeState(CatanState* newState, string info) {

	/*
	* Guardo el mensaje descriptivo con informacion del cambio
	* de estado, en caso de que tenga informacion o contenido
	*/
	if (info.size()) {
		description = info;
	}

	/*
	* Para cada uno de los estados, voy a llamar a sus constructores
	* y a la sobrecarga de cambio de estado ya creada.
	*/
	changeState(newState);
}

void
CatanGame::changeState(CatanState* newState) {

	/* Borro el previo */
	if(prevState)
		delete prevState;

	/* Guardo previo */
	prevState = state;

	/* Actualizo y cambio */
	state = newState;

	/* Notifico el cambio de estado a los observers */
	_notify_change();
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

	/* Notifico el cambio de estado a los observers */
	_notify_change();
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
	resourceMap.insert(pair<Coord, ResourceHex>(coords.back(), ResourceHex(ResourceId::DESERT, coords.back())));
	moveRobber(coords.back());
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

	/* Genero los numeros aleatorios */
	tokens.push_back(2), tokens.push_back(12);
	for (unsigned int i = 3; i <= 11; i++) {
		tokens.push_back(i);
		tokens.push_back(i);
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

bool
CatanGame::verifyMap(map<Coord, MapValue> gameMap) {
	/*
	* Primero verifico que existan en la definicion, todos los puntos
	* del mapa, tanto de tierra como de mar, para lo cual
	* reviso que existan los elementos en el diccionario 
	*/
	map<MapValue, unsigned int> counter;

	for (unsigned char i = MIN_SEA_COORD; i <= MAX_SEA_COORD; i++) {
		if (gameMap.find(i) == gameMap.end()) {
			return false;
		}

		if (counter.find(i) == counter.end()) {
			counter.insert(pair<MapValue, unsigned int>(i, 1));
		}
		else {
			counter[i] += 1;
		}
	}

	for (unsigned char i = MIN_LAND_COORD; i <= MAX_LAND_COORD; i++) {
		if (gameMap.find(i) == gameMap.end()) {
			return false;
		}

		if (counter.find(i) == counter.end()) {
			counter.insert(pair<MapValue, unsigned int>(i, 1));
		}
		else {
			counter[i] += 1;
		}
	}

	/*
	* Luego compruebo que los valores mantengan una relacion 
	* correcta de cantidades, segun lo establecido por las reglas
	* del juego Catan
	*/
	bool verify = (
		counter[(MapValue)ResourceId::DESERT] == DESERT_HEX_COUNT &&
		counter[(MapValue)ResourceId::HILL] == HILL_HEX_COUNT &&
		counter[(MapValue)ResourceId::FOREST] == FOREST_HEX_COUNT &&
		counter[(MapValue)ResourceId::MOUNTAIN] == MOUNTAIN_HEX_COUNT &&
		counter[(MapValue)ResourceId::FIELD] == FIELD_HEX_COUNT &&
		counter[(MapValue)ResourceId::PASTURES] == PASTURE_HEX_COUNT &&
		counter[(MapValue)SeaId::BRICK] == 1 &&
		counter[(MapValue)SeaId::WOOD] == 1 &&
		counter[(MapValue)SeaId::WHEAT] == 1 &&
		counter[(MapValue)SeaId::SHEEP] == 1 &&
		counter[(MapValue)SeaId::STONE] == 1 &&
		counter[(MapValue)SeaId::NORMAL] == 1
	);

	return verify;
}

bool
CatanGame::verifyTokens(map<Coord, unsigned char> tokens) {

	/*
	* Verifico que esten los tokens de todas las posiciones 
	* y luego valido que los numeros esten en el rango que se 
	* admite segun las reglas de Catan
	*/
	map<unsigned int, unsigned int> tokenCounter;

	for (unsigned int i = 3; i <= 11; i++) tokenCounter.insert(pair<unsigned int, unsigned int>(i, 2));
	tokenCounter.insert(pair<unsigned int, unsigned int>(2, 1));
	tokenCounter.insert(pair<unsigned int, unsigned int>(12, 1));

	for (unsigned int i = MIN_LAND_COORD; i <= MAX_LAND_COORD; i++) {

		if (tokenCounter.find(i) == tokenCounter.end()) {
			return false;
		}else if( tokenCounter[i] > 0 ){
			tokenCounter[i] -= 1;
		}
		else if( tokenCounter[i] == 0) {
			return false;
		}
	}

	return true;
}

void
CatanGame::setGlobalMap(map<Coord, MapValue> gameMap, map<Coord, unsigned char> tokens) {

	/*
	* Limpio los mapas actuales 
	*/
	resourceMap.clear();
	seaMap.clear();

	/*
	* Construyo todos los ResourceHex recibidos con sus tokens
	* y luego los agrego al mapa de tierras
	*/
	for (unsigned char i = MIN_LAND_COORD; i <= MAX_LAND_COORD; i++) {
		
		ResourceHex hex = ResourceHex((ResourceId)gameMap[i], (unsigned int)tokens[i], i);
		resourceMap.insert( pair<Coord, ResourceHex>(i, hex) );

		/* Ubicamos el robber */
		if (hex.getResource() == ResourceId::DESERT) {
			moveRobber(hex.getCoord());
		}
	}

	/*
	* Luego realizo la misma accion pero con las piezas de mar, agregando las que 
	* corresponden al mapa
	*/
	for (unsigned int i = MIN_SEA_COORD; i <= MAX_SEA_COORD; i++) {

		SeaHex hex = SeaHex(i, (SeaId)gameMap[i]);
		seaMap.insert( pair<Coord, SeaHex>(i, hex) );
	}
}

void
CatanGame::setTurn(PlayerId playerId) {
	turn = playerId;
}

void
CatanGame::toggleTurn(void) {
	turn = OPONENT_ID(turn);
}

bool
CatanGame::validDices(unsigned int dices) {
	return (dices > 2 && dices < 12);
}

bool
CatanGame::validDices(unsigned int fDice, unsigned int sDice) {
	return (fDice <= 6 && fDice >= 1) && (sDice <= 6 && sDice >= 1);
}

void
CatanGame::assignResources(unsigned int dices) {

	/* Identifico las coordenadas en las cuales el token coincide
	* con el valor dado de dices, para entregar ese recurso */
	list<ResourceHex> hits;
	for (auto hex : resourceMap) {
		ResourceHex resourceHex = hex.second;
		if (resourceHex.getToken() == dices) {
			if ( !(resourceHex.getCoord() == robber.getCoord()) ) {
				hits.push_back(resourceHex);
			}
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
CatanGame::assignResources(BuildingType type, Coord coords, PlayerId playerId) {
	
	/*
	* Verifico que si la coordenada corresponde correctamente a un punto
	* , busco para cada uno de los hexagonos de recursos, y se lo asigno al player como
	* corresponde.
	*/
	if (coords.isDot() && type != BuildingType::ROAD) {
		list<Coord> landCoords = coords.getLandCoords();
		
		for (Coord coord : landCoords) {
			ResourceHex resourceHex = resourceMap[coord];
			assignResources(playerId, resourceHex.getResource(), type == BuildingType::CITY ? 2 : 1);
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
	* Inicializo los valores del longest road de cada jugador y asumo
	* estado de visitas false en todos los caminos posibles 
	*/
	playerLongestRoad[PlayerId::PLAYER_ONE] = 0;
	playerLongestRoad[PlayerId::PLAYER_TWO] = 0;

	/*
	* Pruebo hacer recorrido desde todos los buildings posibles,
	* en cada caso si ya fue visitado, directamente el algoritmo saldra
	* habiendo tenido una longitud nula. Quedan despues guardados los caminos.
	*/
	for (Building* building : builtMap) {
		getLongestRoad(building);
	}

	/*
	* Limpio las marcas realizadas en todos los buildings y reviso si los
	* resultados de los recorridos superaron el valor actual 
	*/
	for (Building* building : builtMap) building->visit(false);

	/*
	* Verifico si con los nuevos resultados cambia el estado del longest road y luego
	* hago el intercambio de los puntajes nuevamente
	*/
	if (playerLongestRoad[PlayerId::PLAYER_ONE] >= MIN_LONGEST_ROAD && playerLongestRoad[PlayerId::PLAYER_TWO] >= MIN_LONGEST_ROAD) {
		if (longestRoad == PlayerId::PLAYER_ONE && (playerLongestRoad[PlayerId::PLAYER_TWO] > playerLongestRoad[PlayerId::PLAYER_ONE])) {
			longestRoad = PlayerId::PLAYER_TWO;
			getPlayer(PlayerId::PLAYER_TWO).addPoints(LONGEST_ROAD_POINTS);
			getPlayer(PlayerId::PLAYER_ONE).removePoints(LONGEST_ROAD_POINTS);
		}
		else if (longestRoad == PlayerId::PLAYER_TWO && (playerLongestRoad[PlayerId::PLAYER_ONE] > playerLongestRoad[PlayerId::PLAYER_TWO])) {
			longestRoad = PlayerId::PLAYER_ONE;
			getPlayer(PlayerId::PLAYER_ONE).addPoints(LONGEST_ROAD_POINTS);
			getPlayer(PlayerId::PLAYER_TWO).removePoints(LONGEST_ROAD_POINTS);
		}
	}
	else if (playerLongestRoad[PlayerId::PLAYER_ONE] >= MIN_LONGEST_ROAD) {
		getPlayer(PlayerId::PLAYER_ONE).addPoints(LONGEST_ROAD_POINTS);
		longestRoad = PlayerId::PLAYER_ONE;
	}
	else if (playerLongestRoad[PlayerId::PLAYER_TWO] >= MIN_LONGEST_ROAD) {
		getPlayer(PlayerId::PLAYER_TWO).addPoints(LONGEST_ROAD_POINTS);
		longestRoad = PlayerId::PLAYER_TWO;
	}
}

void
CatanGame::getLongestRoad(Building* building, unsigned int length) {
	/*
	* Recorro todos los caminos que se bifurcan de building por sus vecinos
	* y en cada uno de ellos llevo la cuenta del largo del camino, cuando termino
	* se revisa si es el mas largo al momento, y hace un update de la variable
	* de clase playerLongesRoad
	*/

	if (building->wasVisited()) {
		/*
		* Ya fue visitado, entonces termino el camino aca, debo actualizar
		* si se dan las condiciones...
		*/
		if (length > playerLongestRoad[building->getPlayer()]) {
			playerLongestRoad[building->getPlayer()] = length;
		}
	}
	else {
		building->visit();

		/* Como no fue visitando antes, entonces incrementa el largo del camino
		* hasta el momento */
		length += building->getType() == BuildingType::ROAD ? 1 : 0;

		/*
		* Si no fue visitado, existen dos posibilidades, que no tenga mas vecinos
		* en cuyo caso tambien termina de visitar y luego la otra chance, que siga vistiando
		* a sus vecinos
		*/
		if (building->hasNeighbours()) {

			/* Visito a cada uno de los vecinos nuevamente
			* con un recorrido de tipo DFS, en profunidad
			*/
			for (Building* neighbour : building->getNeighbours()) {
				getLongestRoad(neighbour, length);
			}
		}
		else {
			if (length > playerLongestRoad[building->getPlayer()]) {
				playerLongestRoad[building->getPlayer()] = length;
			}
		}
	}
}

bool
CatanGame::isRobberDices(unsigned int dices) {
	return dices == ROBBER_CARDS_COUNT;
}

bool
CatanGame::hasRobberCards(PlayerId playerID) {
	return (getPlayer(playerID).getResourceCount() > ROBBER_CARDS_COUNT);
}

bool
CatanGame::validateRobberCards(list<ResourceCard*>& cards, PlayerId playerID) {

	/*
	* Calculo la cantidad de cartas que debiera entregar el jugador
	* correspondiente, y lo almaceno temporalmente
	*/
	unsigned int shouldGive = getPlayer(playerID).getResourceCount() / 2;

	/* 
	* Valido la cantidad de cartas entregadas
	*/
	return cards.size() == shouldGive;
}

bool
CatanGame::validateRobberCards(list<ResourceId>& cards, PlayerId playerID) {

	/*
	* Calculo la cantidad de cartas que debiera entregar el jugador
	* correspondiente, y lo almaceno temporalmente
	*/
	unsigned int shouldGive = getPlayer(playerID).getResourceCount() / 2;

	/*
	* Valido la cantidad de cartas entregadas
	*/
	return cards.size() == shouldGive;
}

void
CatanGame::robberCards(list<ResourceCard*>& cards, PlayerId playerID) 
{
	Player& player = getPlayer(playerID);

	for (ResourceCard* card : cards)
	{
		player.removeResourceCard(card);
		delete card;
	}
}

void
CatanGame::robberCards(list<ResourceId>& cards, PlayerId playerID) {
	Player& player = getPlayer(playerID);

	for (ResourceId card : cards) {
		player.removeResourceCard(card);
	}
}

bool
CatanGame::validRobberMovement(Coord coord) {

	/*
	* Verifico que el robber vaya a una ubicacion valida
	* en tierra y luego me fijo que este cambiando de posicion
	*/
	if (coord.isLand()) {
		if (!(coord == robber.getCoord())) {
			return true;
		}
	}
	return false;
}

void
CatanGame::moveRobber(Coord newCoords) {
	robber.setCoord(newCoords);
}

void
CatanGame::updateDocks(Coord coord, PlayerId playerId) {

	/* Verifico inicialmente que la coordenada
	* corresponda a un asentamiento o a una ciudad como es debido */
	if (coord.isDot()) {

		/*
		* Busco entre todas las piezas del mapa de mares, si alguna
		* posee en esa coordenada un dock, luego, en caso de haberlo,
		* obtengo el tipo de muelle y, antes de agregarlo a la lista,
		* verifico que no este ya añadido.
		*/
		for (auto waterHex : seaMap) {
			SeaHex seaHex = waterHex.second;

			if (seaHex.hasDock(coord)) {

				SeaId seaId = seaHex.dockType(coord);
				list<SeaId>& dockList = playerDocks[playerId];
				if (find(dockList.begin(), dockList.end(), seaId) == dockList.end()) {
					dockList.push_back(seaId);
				}
				break;
			}
		}
	}
}

Building*
CatanGame::isValidRoad(Coord coords, PlayerId playerID) {

	/* Valido que la coordenada sea valida, verificando que sea
	* de tipo EDGE, y luego chequeo si no esta ocupada aun por otra
	* construccion de algun jugador o el mismo 
	*/
	if (coords.isEdge()) {

		for (Building* building : builtMap) {
			if (building->getPlace() == coords) {
				return nullptr;
			}
		}

		/*
		* A continuacion, si no fallo la validacion previa, se verifica
		* que exista algun punto o linea a la cual adherir el camino,
		* para continuar el camino, en caso encontrarlo se devuelve el puntero
		*/
		for (Building* building : builtMap) {

			/* En las construcciones del jugador */
			if (building->getPlayer() == playerID) {

				/* Aquellas que son ROADS */
				if (building->getType() == BuildingType::ROAD) {

					/* Si son una continuidad el ROAD con el ROAD */
					if (coords.edgeContinuity(building->getPlace())) {
						Coord checkCoord(coords, building->getPlace());

						/* Verifico que no tengan en medio un settlement enemigo :( */
						for (Building* otherBuilding : builtMap) {
							if (otherBuilding->getPlayer() == OPONENT_ID(playerID)) {
								if (otherBuilding->getPlace() == checkCoord) {
									return nullptr;
								}
							}
						}
						return building;
					}
				}
				else {
					/* Si son CITIES o SETTLEMENTS, y se conectan con el ROAD */
					if (coords.isEdgeOf(building->getPlace())) {
						return building;
					}
				}
			}
		}
	}

	return nullptr;
}

Building*
CatanGame::isValidCity(Coord coords, PlayerId playerID) {

	/*
	* Verifico primero que la coordenada corresponda a una ubicacion
	* puntual para asentamientos o ciudades y luego verifico si hay
	* en esa coordenada, otro settlement para reemplazar
	*/
	if (coords.isDot()) {

		for (Building* building : builtMap) {

			if (building->getPlayer() == playerID) {

				if (building->getPlace() == coords) {

					if (building->getType() == BuildingType::SETTLEMENT) {
						return building;
					}
					else {
						return nullptr;
					}
				}
			}
		}
	}
	return nullptr;
}

Building*
CatanGame::isValidSettlement(Coord coords, PlayerId playerID) {

	/*
	* Verifico que sea una coordenada valida para poder establecer
	* un asentamiento, y luego verifico que no este ya utilizada
	* por otro asentamiento o ciudad
	*/
	if (coords.isDot()) {
		for (Building* building : builtMap) {
			if (building->getPlace() == coords) {
				return nullptr;
			}
		}

		/*
		* Busco entre los roads construidos del jugador, a ver si alguno
		* se conecta con el punto de interes, y luego verifico que ningun otro
		* establecimiento sea adyacente
		*/
		for (Building* building : builtMap) {
			/* Busco caminos del jugador en cuestion */
			if (building->getPlayer() == playerID) {
				if (building->getType() == BuildingType::ROAD) {

					/* Encuentro un camino que conecte a ese settlement */
					if (coords.isEdgeOf(building->getPlace())) {

						/* Verifico la regla de la distancia */
						for (Building* building : builtMap) {

							if (building->getType() != BuildingType::ROAD) {

								if (coords.isAdjacentDot(building->getPlace())) {
									return nullptr;
								}
							}
						}

						return building;
					}
				}
			}
		}
	}

	return nullptr;
}

bool 
CatanGame::validFirstSettlement(Coord coords, PlayerId playerId) {

	/*
	* Verifico que la construccion sea en una coordenada valida
	* y luego verifico que no existe ninguna construccion en ese punto
	*/
	if (coords.isDot()) {
		for (Building* building : builtMap) {
			if (building->getPlace() == coords) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool
CatanGame::hasCityResources(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	return (
		player.getResourceCount(ResourceId::MOUNTAIN) >= CITY_ORE_NEEDED &&
		player.getResourceCount(ResourceId::FIELD) >= CITY_GRAIN_NEEDED
		);
}

bool 
CatanGame::hasSettlementResources(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	return(
		player.getResourceCount(ResourceId::HILL) >= SETTLEMENT_BRICK_NEEDED &&
		player.getResourceCount(ResourceId::FIELD) >= SETTLEMENT_GRAIN_NEEDED &&
		player.getResourceCount(ResourceId::FOREST) >= SETTLEMENT_LUMBER_NEEDED &&
		player.getResourceCount(ResourceId::PASTURES) >= SETTLEMENT_WOOL_NEEDED
		);
}

bool
CatanGame::hasRoadResources(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	return (
		player.getResourceCount(ResourceId::HILL) >= ROAD_BRICK_NEEDED &&
		player.getResourceCount(ResourceId::FOREST) >= ROAD_LUMBER_NEEDED
		);
}

void
CatanGame::buildRoad(Building* building, Coord coords, PlayerId playerID)
{

	/*
	* Busco un camino de entre las fichas del jugador y 
	* lo configuro para conectarrlo al building dado, en ambos
	* sentidos
	*/
	Building* newRoad = getPlayer(playerID).popRoad();
	newRoad->setPlace(coords);
	newRoad->addNeighbour(building);
	building->addNeighbour(newRoad);
	
	/*
	* Agrego la ficha al tablero del mapa de construcciones realizadas
	* y configuro los puntos del jugador 
	*/
	builtMap.push_back(newRoad);
	getPlayer(playerID).addPoints(ROAD_BUILT_POINTS);

	/* Actualizo camino mas largo */
	updateLongestRoad();

	/* Actualizo los puntos y veo ganador */
	updateWinner();
}

void
CatanGame::buildCity(Building* building, Coord coords, PlayerId playerID)
{

	/*
	* Extraigo una ciudad de entre las fichas del jugador y luego
	* le configuro las conexiones correspondientes
	*/
	Building* newCity = getPlayer(playerID).popCity();
	newCity->setPlace(coords);
	newCity->addNeighbour( building->getNeighbours() );
	building->removeNeighbour();
	for (Building* neighbours : newCity->getNeighbours()) {
		neighbours->removeNeighbour(building);
		neighbours->addNeighbour(newCity);
	}

	/*
	* Agrego la ciudad entre el tablero de construcciones del juego
	* y modifico las puntaciones correspondientes, ademas, devuelvo
	* la ficha al player
	*/
	builtMap.remove(building);
	builtMap.push_back(newCity);
	getPlayer(playerID).giveBackBuilding(BuildingType::SETTLEMENT, building);
	getPlayer(playerID).removePoints(SETTLEMENT_BUILT_POINTS);
	getPlayer(playerID).addPoints(CITY_BUILT_POINTS);

	/* Actualizo los puntos y veo ganador */
	updateWinner();
}

void
CatanGame::buildSettlement(Building* building, Coord coords, PlayerId playerID)
{
	/* Extraigo un asentamiento entre las fichas del jugador para luego
	* agregar las conexiones entre el anterior y este, ademas de su ubicacion
	*/
	Building* newSettlement = getPlayer(playerID).popSettlement();
	newSettlement->setPlace(coords);
	if (building) {
		newSettlement->addNeighbour(building);
		building->addNeighbour(newSettlement);
	}

	/*
	* Agrego la nueva construccion al tablero y le asigno el puntaje
	*/
	builtMap.push_back(newSettlement);
	getPlayer(playerID).addPoints(SETTLEMENT_BUILT_POINTS);

	/* Actualizo los docks disponibles del usuario/jugador */
	updateDocks(coords, playerID);

	/* Actualizo los puntos y veo ganador */
	updateWinner();
}

void
CatanGame::payRoad(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	player.removeResourceCard(ResourceId::FOREST, ROAD_LUMBER_NEEDED);
	player.removeResourceCard(ResourceId::HILL, ROAD_BRICK_NEEDED);
}

void
CatanGame::payCity(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	player.removeResourceCard(ResourceId::MOUNTAIN, CITY_ORE_NEEDED);
	player.removeResourceCard(ResourceId::FIELD, CITY_GRAIN_NEEDED);
}

void
CatanGame::paySettlement(PlayerId playerID) {
	Player& player = getPlayer(playerID);

	player.removeResourceCard(ResourceId::HILL, SETTLEMENT_BRICK_NEEDED);
	player.removeResourceCard(ResourceId::FOREST, SETTLEMENT_LUMBER_NEEDED);
	player.removeResourceCard(ResourceId::PASTURES, SETTLEMENT_WOOL_NEEDED);
	player.removeResourceCard(ResourceId::FIELD, SETTLEMENT_GRAIN_NEEDED);
}

bool
CatanGame::accepts(list<ResourceId>& cards, unsigned int qty, ResourceId id) {

	/* Verifico que la cantidad de cartas sea la pedida,
	* y luego guardo y verifico que sean todas del mismo tipo
	*/
	ResourceId resourceId = id;
	if (cards.size() == qty) {
		for (ResourceId card : cards) {
			if (card != resourceId) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool
CatanGame::accepts(list<ResourceId>& cards, unsigned int qty) {

	/* Verifico que la cantidad de cartas sea la pedida,
	* y luego guardo y verifico que sean todas del mismo tipo
	*/
	ResourceId resourceId = cards.front();
	if (cards.size() == qty) {
		for (ResourceId card : cards) {
			if (card != resourceId) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool
CatanGame::accepts(list<ResourceCard*>& cards, unsigned int qty, ResourceId id) {

	/* Verifico que la cantidad de cartas sea la pedida,
	* y luego guardo y verifico que sean todas del mismo tipo
	*/
	ResourceId resourceId = id;
	if (cards.size() == qty) {
		for (ResourceCard* card : cards) {
			if (card->getResourceId() != resourceId) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool 
CatanGame::accepts(list<ResourceCard*>& cards, unsigned int qty) {
	
	/* Verifico que la cantidad de cartas sea la pedida,
	* y luego guardo y verifico que sean todas del mismo tipo
	*/
	ResourceId resourceId = cards.front()->getResourceId();
	if (cards.size() == qty) {
		for (ResourceCard* card : cards) {
			if (card->getResourceId() != resourceId) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool 
CatanGame::isValidDockExchange(list<ResourceCard*>& offeredCards, PlayerId playerId) {

	/*
	* Primero verifico que tenga docks disponibles, luego reviso en cada uno de ellos
	* segun su tipo, si la accion del usuario es valida
	*/
	list<SeaId>& docks = playerDocks[playerId];
	if (docks.size()) {
		for (SeaId seaId : docks) {
			switch (seaId) {
			case SeaId::NORMAL:
				if (accepts(offeredCards, NORMAL_COUNT)) {
					return true;
				}
				break;
			case SeaId::WHEAT:
				if (accepts(offeredCards, WHEAT_COUNT, ResourceId::FIELD)) {
					return true;
				}
				break;
			case SeaId::BRICK:
				if (accepts(offeredCards, BRICK_COUNT, ResourceId::HILL)) {
					return true;
				}
				break;
			case SeaId::SHEEP:
				if (accepts(offeredCards, SHEEP_COUNT, ResourceId::PASTURES)) {
					return true;
				}
				break;
			case SeaId::STONE:
				if (accepts(offeredCards, STONE_COUNT, ResourceId::MOUNTAIN)) {
					return true;
				}
				break;
			case SeaId::WOOD:
				if (accepts(offeredCards, WOOD_COUNT, ResourceId::FOREST)) {
					return true;
				}
				break;
			}
		}
	}
	return false;
}

bool
CatanGame::isValidDockExchange(list<ResourceId>& offeredCards, PlayerId playerId) {

	/*
	* Primero verifico que tenga docks disponibles, luego reviso en cada uno de ellos
	* segun su tipo, si la accion del usuario es valida
	*/
	list<SeaId>& docks = playerDocks[playerId];
	if (docks.size()) {
		for (SeaId seaId : docks) {
			switch (seaId) {
				case SeaId::NORMAL:
					if (accepts(offeredCards, NORMAL_COUNT)) {
						return true;
					}
					break;
				case SeaId::WHEAT:
					if (accepts(offeredCards, WHEAT_COUNT, ResourceId::FIELD)) {
						return true;
					}
					break;
				case SeaId::BRICK:
					if (accepts(offeredCards, BRICK_COUNT, ResourceId::HILL)) {
						return true;
					}
					break;
				case SeaId::SHEEP:
					if (accepts(offeredCards, SHEEP_COUNT, ResourceId::PASTURES)) {
						return true;
					}
					break;
				case SeaId::STONE:
					if (accepts(offeredCards, STONE_COUNT, ResourceId::MOUNTAIN)) {
						return true;
					}
					break;
				case SeaId::WOOD:
					if (accepts(offeredCards, WOOD_COUNT, ResourceId::FOREST)) {
						return true;
					}
					break;
			}
		}
	}
	return false;
}

bool
CatanGame::isValidPlayerExchange(list<ResourceCard*>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	/*
	* Verifico que ambos jugadores tengan las cartas disponibles
	* para poder realizar el intercambio
	*/
	if (offeredCards.size() > 9 || requestedCards.size() > 9) {
		return false;
	}

	return	(
		canPlayerAccept(offeredCards, srcPlayerID) &&
		canPlayerAccept(requestedCards, (OPONENT_ID(srcPlayerID)))
	);

}

bool
CatanGame::isValidPlayerExchange(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	/*
	* Verifico que ambos jugadores tengan las cartas disponibles
	* para poder realizar el intercambio, y ademas, verifico que la cantidad
	* no se pase del maximo valor de transacciones posibles
	*/
	if (offeredCards.size() > 9 || requestedCards.size() > 9) {
		return false;
	}

	return	(
		canPlayerAccept(offeredCards, srcPlayerID) &&
		canPlayerAccept(requestedCards, (OPONENT_ID(srcPlayerID)))
	);
}

bool
CatanGame::isValidBankExchange(list<ResourceCard*>& offeredCards, PlayerId playerID) {

	return accepts(offeredCards, BANK_TRANSACTION_CARDS_COUNT) && canPlayerAccept(offeredCards, playerID);
}

bool
CatanGame::isValidBankExchange(list<ResourceId>& offeredCards, PlayerId playerID) {

	return accepts(offeredCards, BANK_TRANSACTION_CARDS_COUNT) && canPlayerAccept(offeredCards, playerID);
}

bool
CatanGame::canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID)
{
	/*
	* Verifico que la cantidad de recursos de cada tipo que el jugador tiene
	* sea superior o equivalente a la cantidad en la lista de cartas que se piden
	*/
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
	/*
	* Verifico que la cantidad de recursos de cada tipo que el jugador tiene
	* sea superior o equivalente a la cantidad en la lista de cartas que se piden
	*/
	list<ResourceId> cards;

	for (ResourceCard* card : requestedCards) {
		cards.push_back(card->getResourceId());
	}

	return canPlayerAccept(cards, destPlayerID);
}

void
CatanGame::Exchange(list<ResourceCard*>& offered, ResourceId wanted, PlayerId playerID)
{
	/*
	* Para realizar un intercambio de este tipo, primero se remueven todas las cartas
	* dadas por el jugador de su pilon, y luego se agrega la carta pedida, creandola
	* previamente
	*/
	for (ResourceCard* cardOffered : offered)
	{
		getPlayer(playerID).removeResourceCard(cardOffered);
	}

	/*
	* Creo la carta pedida y se la entrego al jugador en cuestion
	*/
	ResourceCard* newCard = new ResourceCard(playerID, wanted);
	getPlayer(playerID).addResourceCard(newCard);
}

void
CatanGame::Exchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID)
{
	/*
	* Para realizar un intercambio de este tipo, primero se remueven todas las cartas
	* dadas por el jugador de su pilon, y luego se agrega la carta pedida, creandola
	* previamente
	*/
	for (ResourceId cardOffered : offered)
	{
		getPlayer(playerID).removeResourceCard(cardOffered);
	}

	/*
	* Creo la carta pedida y se la entrego al jugador en cuestion
	*/
	ResourceCard* newCard = new ResourceCard(playerID, wanted);
	getPlayer(playerID).addResourceCard(newCard);
}

void
CatanGame::playerExchange(list<ResourceCard*>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID)
{
	PlayerId oponent = OPONENT_ID(srcPlayerID);

	/*
	* Primero busco todas las cartas ofrecidas por el jugador y tomo cada una de ellas,
	* luego la modifico y la entrego al otro jugador, verificando el contenido de la misma
	*/
	for (ResourceCard* cardOffered : offered)
	{
		cardOffered->setPlayerId(oponent);
		getPlayer(oponent).addResourceCard(cardOffered);
		getPlayer(srcPlayerID).removeResourceCard(cardOffered);
	}

	/*
	* Busco las cartas del segundo jugador, las cuales primero modifico, y luego quito y entrego
	* al que las recibe
	*/
	for (ResourceId card : wanted) {
		ResourceCard* cardWanted = getPlayer(oponent).getResourceCard(card);
		cardWanted->setPlayerId(srcPlayerID);
		getPlayer(srcPlayerID).addResourceCard(cardWanted);
	}
}

void
CatanGame::playerExchange(list<ResourceId>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID)
{
	PlayerId oponent = OPONENT_ID(srcPlayerID);

	/*
	* Primero busco todas las cartas ofrecidas por el jugador y tomo cada una de ellas,
	* luego la modifico y la entrego al otro jugador, verificando el contenido de la misma
	*/
	for (ResourceId card : offered)
	{
		ResourceCard* cardOffered = getPlayer(srcPlayerID).getResourceCard(card);
		cardOffered->setPlayerId(oponent);
		getPlayer(oponent).addResourceCard(cardOffered);
	}

	/*
	* Busco las cartas del segundo jugador, las cuales primero modifico, y luego quito y entrego
	* al que las recibe
	*/
	for (ResourceId card : wanted) {
		ResourceCard* cardWanted = getPlayer(oponent).getResourceCard(card);
		cardWanted->setPlayerId(srcPlayerID);
		getPlayer(srcPlayerID).addResourceCard(cardWanted);
	}
}

void
CatanGame::pass() {
	this->turn = OPONENT_ID(this->turn);
}

bool
CatanGame::hasWinner(void) {
	return winner != PlayerId::PLAYER_NONE;
}

PlayerId
CatanGame::getWinner(void) {
	return winner;
}

void
CatanGame::updateWinner(void) {
	if (localPlayer.getVictoryPoints() == WINNER_POINTS) {
		winner = PlayerId::PLAYER_ONE;
	}
	else if (remotePlayer.getVictoryPoints() == WINNER_POINTS) {
		winner = PlayerId::PLAYER_TWO;
	}
}