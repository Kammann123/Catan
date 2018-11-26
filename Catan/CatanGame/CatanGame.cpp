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
			resourceMap.insert(pair<unsigned char, ResourceHex>(hex.getCoord(), hex));
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
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL, SeaId::SHEEP))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL, SeaId::BRICK))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL))), coords.pop_back();
	seaMap.insert(pair<unsigned char, SeaHex>(coords.back(), SeaHex(coords.back(), SeaId::NORMAL, SeaId::WHEAT))), coords.pop_back();
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

}

void
CatanGame::buildCity(string coords, PlayerId playerID) {

}

void
CatanGame::buildSettlement(string coords, PlayerId playerID) {

}

bool 
CatanGame::isValidDockExchange(list<ResourceId>& offeredCards, ResourceId requestedCard, unsigned char seaCoord, unsigned char dockNumber, PlayerId player) {

	return false;
}

bool
CatanGame::isValidPlayerExchange(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	return false;

}

bool 
CatanGame::isValidBankExchange(list<ResourceId>& offeredCards, PlayerId playerID) {

	return false;
}

bool
CatanGame::isAvailableDock(SeaId dockID, PlayerId playerID) {

	return false;
}

bool
CatanGame::canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID) {
	return false;
}

void
CatanGame::bankExchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID) {

}

void
CatanGame::playerExchange(list<ResourceId>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID) {

}

void
CatanGame::dockExchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID) {

}

void
CatanGame::pass() {
	this->turn = (this->turn == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE);
}

/*
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
*/
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
*/
