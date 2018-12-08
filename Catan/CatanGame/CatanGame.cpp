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
#include "CatanStates/GameError.h"

#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

#include <algorithm>
#include <vector>
#include <time.h>

const char* CatanGame::StateString[10] = { 
	"GAME_SYNC", "FIRST_BUILDS", "THROW_DICES", 
	"ROBBER_CARD", "ROBBER_MOVE", "TURN", 
	"OFFER_ANSWER", "WINNER", "GAME_END", "GAME_ERROR"
};

void 
CatanGame::_create_remote_player(void) {
	remotePlayer = new Player(PlayerId::PLAYER_TWO, this);
}

void
CatanGame::_create_local_player(void) {
	localPlayer = new Player(PlayerId::PLAYER_ONE, this);
}

void
CatanGame::_create_longest_road(void) {
	longestRoad = new LongestRoad(this);
}

void
CatanGame::_create_cards(void) {
	for (unsigned int ii = 0; ii < 5; ii++) {
		ResourceId hexId;

		switch (ii) {
		case 0:
			hexId = ResourceId::HILL;
			break;
		case 1:
			hexId = ResourceId::FOREST;
			break;
		case 2:
			hexId = ResourceId::MOUNTAIN;
			break;
		case 3:
			hexId = ResourceId::FIELD;
			break;
		case 4:
			hexId = ResourceId::PASTURES;
			break;
		}

		for (unsigned int i = 0; i < AMOUT_OF_CARDS; i++) {
			ResourceCard* hex = new ResourceCard(hexId, this);
			cards.push_back(hex);
		}
	}
}

void
CatanGame::_create_map(void) {
	catanMap = new CatanMap(this);
}

void
CatanGame::_destroy_remote_player(void) {
	if (remotePlayer) {
		delete remotePlayer;
	}
}

void
CatanGame::_destroy_longest_road(void) {
	if (longestRoad) {
		delete longestRoad;
	}
}

void
CatanGame::_destroy_local_player(void) {
	if (localPlayer) {
		delete localPlayer;
	}
}

void
CatanGame::_destroy_states(void) {
	if (prevState) {
		delete prevState;
	}
	if (state) {
		delete state;
	}
}

void
CatanGame::_destroy_events(void){
	for (CatanEvent* event : eventQueue) {
		if (event) {
			delete event;
		}
	}
}

void
CatanGame::_destroy_cards(void) {
	for (ResourceCard* card : cards) {
		if (card) {
			delete card;
		}
	}
}

void
CatanGame::_destroy_map(void) {
	if (catanMap) {
		delete catanMap;
	}
}

void
CatanGame::notifyChange(void) {
	/* Notifico a los observers */
	notifyObservers();

	/* Elimino el ultimo evento leido */
	if (hasEvents()) {
		CatanEvent* event = this->eventQueue.front();
		this->eventQueue.pop_front();
		delete event;
	}
}

CatanGame::
CatanGame(void) : ContainerUI(GAME_ID, 0, 0) {
	this->setUIDestroy(false);

	/* Inicializo parametros del juego */
	this->confirmationPlayer = PlayerId::PLAYER_NONE;
	this->winner = PlayerId::PLAYER_NONE;
	this->turn = PlayerId::PLAYER_NONE;
	this->state = new GameSync(*this);
	this->prevState = nullptr;
	this->description = "";

	playerLongestRoad.clear();
	playerDocks.clear();
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_ONE, 0));
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_TWO, 0));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_ONE, {}));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_TWO, {}));

	this->eventQueue.clear();

	/* Creo los componentes del juego */
	_create_remote_player();
	_create_local_player();
	_create_longest_road();
	_create_cards();
	_create_map();

	srand(time(NULL));
}

CatanGame::
~CatanGame() {

	/* Destruyo todos los componentes del juego */
	_destroy_remote_player();
	_destroy_local_player();
	_destroy_longest_road();
	_destroy_states();
	_destroy_events();
	_destroy_cards();
	_destroy_map();
}

void
CatanGame::syncHandle(NetworkPacket* packet) {
	CatanEvent* newEvent = this->getPacketEvent(packet);
	if (newEvent) {
		syncHandle(newEvent);
	}
}

void
CatanGame::syncHandle(CatanEvent* event) {
	if (wasConfirmed()) {
		if (event) {

			/*
			* Valido que el evento particular no sea de cierre
			* en cuyo caso... adios!
			*/
			if (event->getEvent() == CatanEvent::Events::QUIT) {
				changeState(new GameEnd(*this), "[CatanGame] El juego ha finalizado por cierre de alguna de las partes.");
			}
			else {
				this->state->handle(event);

				if (getState() != GAME_SYNC && getState() != GAME_END && getState() != GAME_ERROR) {
					waitConfirmation(OPONENT_ID(event->getPlayer()));
				}

				/* Notifico el cambio de estado a los observers */
				notifyChange();
			}
		}
	}else {
		this->changeState(new GameError(*this), "[CatanGame] Se intento realizar una accion de juego sin la confirmacion de la accion previa!");
		delete event;
	}
}

void
CatanGame::waitConfirmation(PlayerId player) {
	confirmationPlayer = player;
}

void
CatanGame::confirm(PlayerId player) {
	if (player == confirmationPlayer) {
		confirmationPlayer = PlayerId::PLAYER_NONE;
	}
}

PlayerId
CatanGame::whoConfirms(void) {
	return confirmationPlayer;
}

bool
CatanGame::wasConfirmed(void) {
	return confirmationPlayer == PlayerId::PLAYER_NONE;
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
			changeState(new GameEnd(*this), "[CatanGame] El juego ha finalizado por cierre de alguna de las partes.");
		}
		else {
			this->state->handle(event);
		}

		/* Notifico el cambio de estado a los observers */
		notifyChange();
	}
}

const char*
CatanGame::getStateString(void) {
	return StateString[this->state->getId()];
}

CatanGame::State
CatanGame::getState(void) {
	return (State)this->state->getId();
}

void
CatanGame::setInfo(string info) {
	this->description = info;
}

string
CatanGame::info(void) {
	return description;
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

bool
CatanGame::hasEvents(void) const {
	return !(this->eventQueue.empty());
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
	notifyChange();
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

list<ResourceCard*>
CatanGame::getCards(void) {
	return cards;
}

LongestRoad*
CatanGame::getLongestRoad(void) {
	return longestRoad;
}

Player*
CatanGame::getRemotePlayer(void) {
	return remotePlayer;
}

Player*
CatanGame::getLocalPlayer(void) {
	return localPlayer;
}

CatanMap*
CatanGame::getCatanMap(void) {
	return catanMap;
}

list<ResourceCard*>
CatanGame::takeCards(ResourceId id, unsigned int qty) {
	list<ResourceCard*> taken;
	for (ResourceCard* card : cards) {
		if (card) {
			if (card->getResourceId() == id) {
				taken.push_back(card), qty--;
				if (qty == 0) {
					break;
				}
			}
		}
	}
	return taken;
}

void
CatanGame::returnCards(list<ResourceCard*> cards) {
	for (ResourceCard* card : cards) {
		if (card) {
			returnCards(card);
		}
	}
}

void
CatanGame::returnCards(ResourceCard* card) {
	cards.push_back(card);
}

bool
CatanGame::isRobberStatus() {
	return state->getId() == State::ROBBER_CARD || state->getId() == State::ROBBER_MOVE;
}

Player*
CatanGame::getPlayer(PlayerId playerId) {
	return playerId == PlayerId::PLAYER_ONE ? localPlayer : remotePlayer;
}

void
CatanGame::resetGame() {

	/* Reincio el puntaje de los jugadores */
	localPlayer->resetVictoryPoints();
	remotePlayer->resetVictoryPoints();

	/* Pido que devuelvan las cartas */
	returnCards(localPlayer->giveAllCards());
	returnCards(remotePlayer->giveAllCards());

	/* Devuelvo las construcciones */
	for (Building* building : catanMap->buildings()) {
		if (building) {
			building->getPlayer()->giveBackBuilding(building);
			catanMap->demolish(building);
			building->removeNeighbour();
		}
	}

	/* Reinicio parametros de la partida */
	this->confirmationPlayer = PlayerId::PLAYER_NONE;
	this->turn = PlayerId::PLAYER_NONE;
	this->winner = PlayerId::PLAYER_NONE;
	this->prevState = nullptr;
	this->state = new GameSync(*this);
	playerLongestRoad.clear();
	playerDocks.clear();
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_ONE, 0));
	playerLongestRoad.insert(pair<PlayerId, unsigned int>(PlayerId::PLAYER_TWO, 0));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_ONE, {}));
	playerDocks.insert(pair<PlayerId, list<SeaId>>(PlayerId::PLAYER_TWO, {}));

}

void
CatanGame::generateTurn() {
	turn = rand() % 2 ? PlayerId::PLAYER_ONE : PlayerId::PLAYER_TWO;
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
	return (dices >= 2 && dices <= 12);
}

bool
CatanGame::validDices(unsigned int fDice, unsigned int sDice) {
	return (fDice <= 6 && fDice >= 1) && (sDice <= 6 && sDice >= 1);
}

void
CatanGame::assignResources(unsigned int dices) {

	/* Identifico las coordenadas en las cuales el token coincide
	* con el valor dado de dices, para entregar ese recurso */
	list<ResourceHex*> hits;
	for (ResourceHex* hex : catanMap->lands()) {
		if (hex->getToken() == dices) {
			if (!(hex->getCoord() == catanMap->robberPosition())) {
				hits.push_back(hex);
			}
		}
	}

	/* Reviso todas las construcciones realizadas por lo usuarios
	* que estan jugando, y las que sean settlement o city, verifico
	* si esta alrededor del hexagono donde cayo el token y por cada
	* aparicio reparto recursos */
	for (Building* building : catanMap->buildings()) {
		if (building->getType() == BuildingType::ROAD)	continue;

		for (ResourceHex* hex : hits) {
			if (building->getPlace().isVertexOf(hex->getCoord())) {
				assignResources(building->getPlayer()->getPlayerId(), hex->getResource(), building->getType() == BuildingType::CITY ? 2 : 1);
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
			ResourceHex* resourceHex = catanMap->land(coord);
			assignResources(playerId, resourceHex->getResource(), type == BuildingType::CITY ? 2 : 1);
		}
	}
}

void
CatanGame::assignResources(PlayerId player, ResourceId resource, unsigned int qty) {
	/*
	* Busco al jugador y luego creo la cantidad de cartas necesaria
	* y le entrego una por una todas las que piden que le asigne
	*/
	Player* playerObject = getPlayer(player);
	playerObject->addCard(takeCards(resource, qty));
	setInfo("[CatanGame] Se han asignado los recursos de la jugada actual!");
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
	for (Building* building : catanMap->buildings()) {
		seekLongestRoad(building);
	}

	/*
	* Limpio las marcas realizadas en todos los buildings y reviso si los
	* resultados de los recorridos superaron el valor actual 
	*/
	for (Building* building : catanMap->buildings()) building->visit(false);

	/*
	* Verifico si con los nuevos resultados cambia el estado del longest road y luego
	* hago el intercambio de los puntajes nuevamente
	*/
	if (playerLongestRoad[PlayerId::PLAYER_ONE] >= MIN_LONGEST_ROAD && playerLongestRoad[PlayerId::PLAYER_TWO] >= MIN_LONGEST_ROAD) {
		if (longestRoad->who() == PlayerId::PLAYER_ONE && (playerLongestRoad[PlayerId::PLAYER_TWO] > playerLongestRoad[PlayerId::PLAYER_ONE])) {
			longestRoad->assign(getPlayer(PlayerId::PLAYER_TWO));
		}
		else if (longestRoad->who() == PlayerId::PLAYER_TWO && (playerLongestRoad[PlayerId::PLAYER_ONE] > playerLongestRoad[PlayerId::PLAYER_TWO])) {
			longestRoad->assign(getPlayer(PlayerId::PLAYER_ONE));
		}
		else {
			return;
		}
	}
	else if (playerLongestRoad[PlayerId::PLAYER_ONE] >= MIN_LONGEST_ROAD) {
		longestRoad->assign(getPlayer(PlayerId::PLAYER_ONE));
	}
	else if (playerLongestRoad[PlayerId::PLAYER_TWO] >= MIN_LONGEST_ROAD) {
		longestRoad->assign(getPlayer(PlayerId::PLAYER_TWO));
	}
	else {
		return;
	}

	setInfo("[CatanGame] La carga de Longest Road ha sido asignada a un nuevo jugador!");
}

bool
CatanGame::isLongestRoad(PlayerId player) {
	return longestRoad->who() == player;
}

void
CatanGame::seekLongestRoad(Building* building, unsigned int length) {
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
		if (length > playerLongestRoad[building->getPlayer()->getPlayerId()]) {
			playerLongestRoad[building->getPlayer()->getPlayerId()] = length;
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
				seekLongestRoad(neighbour, length);
			}
		}
		else {
			if (length > playerLongestRoad[building->getPlayer()->getPlayerId()]) {
				playerLongestRoad[building->getPlayer()->getPlayerId()] = length;
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
	return (getPlayer(playerID)->getResourceCount() > ROBBER_CARDS_COUNT);
}

bool
CatanGame::validateRobberCards(list<ResourceId>& cards, PlayerId playerID) {

	/*
	* Calculo la cantidad de cartas que debiera entregar el jugador
	* correspondiente, y lo almaceno temporalmente
	*/
	unsigned int shouldGive = getPlayer(playerID)->getResourceCount() / 2;

	/*
	* Valido la cantidad de cartas entregadas
	*/
	if (cards.size() == shouldGive) {
		return true;
	}
	else {
		setInfo("[CatanGame] Las cartas elegidas a descartar son invalidas, no cumplen con la cantidad debida.");
		return false;
	}
}

void
CatanGame::robberCards(list<ResourceId>& cards, PlayerId playerID) {
	Player* player = getPlayer(playerID);
	returnCards(player->giveCards(cards));
}

bool
CatanGame::validRobberMovement(Coord coord) {

	/*
	* Verifico que el robber vaya a una ubicacion valida
	* en tierra y luego me fijo que este cambiando de posicion
	*/
	if (coord.isLand()) {
		if (!(coord == catanMap->robberPosition())) {
			return true;
		}
	}

	setInfo("[CatanGame] El Robber no puede mantenerse en la misma posicion! Y debe ir siempre en tierra.");
	return false;
}

void
CatanGame::moveRobber(Coord newCoords) {
	catanMap->moveRobber(newCoords);
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
		for (SeaHex* hex : catanMap->seas()) {
			if (hex->hasDock(coord)) {
				SeaId seaId = hex->dockType(coord);
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

		for (Building* building : catanMap->buildings()) {
			if (building->getPlace() == coords) {
				setInfo("[CatanGame] Ubicacion ocupada por otra construccion!");
				return nullptr;
			}
		}

		/*
		* A continuacion, si no fallo la validacion previa, se verifica
		* que exista algun punto o linea a la cual adherir el camino,
		* para continuar el camino, en caso encontrarlo se devuelve el puntero
		*/
		for (Building* building : catanMap->buildings()) {

			/* En las construcciones del jugador */
			if (building->getPlayer()->getPlayerId() == playerID) {

				/* Aquellas que son ROADS */
				if (building->getType() == BuildingType::ROAD) {

					/* Si son una continuidad el ROAD con el ROAD */
					if (coords.edgeContinuity(building->getPlace())) {
						Coord checkCoord(coords, building->getPlace());

						/* Verifico que no tengan en medio un settlement enemigo :( */
						for (Building* otherBuilding : catanMap->buildings()) {
							if (otherBuilding->getPlayer()->getPlayerId() == OPONENT_ID(playerID)) {
								if (otherBuilding->getPlace() == checkCoord) {
									setInfo("[CatanGame] Esa construccion no cumple la regla de la distancia!");
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

	setInfo("[CatanGame] Para construir un Road es necesario continuar a otra construccion.");
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

		for (Building* building : catanMap->buildings()) {

			if (building->getPlayer()->getPlayerId() == playerID) {

				if (building->getPlace() == coords) {

					if (building->getType() == BuildingType::SETTLEMENT) {
						return building;
					}
					else {
						setInfo("[CatanGame] Una City solo puede ubicarse donde haya un Settlement.");
						return nullptr;
					}
				}
			}
		}
	}

	setInfo("[CatanGame] Una City solo puede ubicarse donde haya un Settlement.");
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
		for (Building* building : catanMap->buildings()) {
			if (building->getPlace() == coords) {
				setInfo("[CatanGame] Ubicacion ocupada por otra construccion!");
				return nullptr;
			}
		}

		/*
		* Busco entre los roads construidos del jugador, a ver si alguno
		* se conecta con el punto de interes, y luego verifico que ningun otro
		* establecimiento sea adyacente
		*/
		for (Building* building : catanMap->buildings()) {
			/* Busco caminos del jugador en cuestion */
			if (building->getPlayer()->getPlayerId() == playerID) {
				if (building->getType() == BuildingType::ROAD) {

					/* Encuentro un camino que conecte a ese settlement */
					if (building->getPlace().isEdgeOf(coords)) {

						/* Verifico la regla de la distancia */
						for (Building* building : catanMap->buildings()) {

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

	setInfo("[CatanGame] Un Settlemente debe colocarse continuando alguna construccion realizada.");
	return nullptr;
}

bool 
CatanGame::validFirstSettlement(Coord coords, PlayerId playerId) {

	/*
	* Verifico que la construccion sea en una coordenada valida
	* y luego verifico que no existe ninguna construccion en ese punto
	*/
	if (coords.isDot()) {
		for (Building* building : catanMap->buildings()) {
			if (building->getPlace() == coords) {
				setInfo("[CatanGame] Ubicacion ocupada por otra construccion!");
				return false;
			}
		}
		return true;
	}

	setInfo("[CatanGame] Solo puede construirse en esquinas!");
	return false;
}

bool
CatanGame::hasCityResources(PlayerId playerID) {
	Player* player = getPlayer(playerID);

	if (player->getResourceCount(ResourceId::MOUNTAIN) >= CITY_ORE_NEEDED && player->getResourceCount(ResourceId::FIELD) >= CITY_GRAIN_NEEDED) {
		return true;
	}
	else {
		setInfo("[CatanGame] No tenes suficientes recursos para hacer eso!");
		return false;
	}
}

bool 
CatanGame::hasSettlementResources(PlayerId playerID) {
	Player* player = getPlayer(playerID);

	if (player->getResourceCount(ResourceId::HILL) >= SETTLEMENT_BRICK_NEEDED && player->getResourceCount(ResourceId::FIELD) >= SETTLEMENT_GRAIN_NEEDED && player->getResourceCount(ResourceId::FOREST) >= SETTLEMENT_LUMBER_NEEDED && player->getResourceCount(ResourceId::PASTURES) >= SETTLEMENT_WOOL_NEEDED) {
		return true;
	}
	else {
		setInfo("[CatanGame] No tenes suficientes recursos para hacer eso!");
		return false;
	}
}

bool
CatanGame::hasRoadResources(PlayerId playerID) {
	Player* player = getPlayer(playerID);

	if ( player->getResourceCount(ResourceId::HILL) >= ROAD_BRICK_NEEDED && player->getResourceCount(ResourceId::FOREST) >= ROAD_LUMBER_NEEDED ) {
		return true;
	}
	else {
		setInfo("[CatanGame] No tenes suficientes recursos para hacer eso!");
		return false;
	}
}

bool
CatanGame::buildingOk(BuildingType type, Coord coords, PlayerId player) {

	/* Valido para cada tipo de construccion si es valido
	* en cuanto a disponibilidad de recursos y luego verifico
	* que sea valida la construccion en cuanto a ubicacion,
	* teniendo en cuenta caso particular de primeros buildings
	*/
	switch (type) {
		case BuildingType::SETTLEMENT:
			if (hasSettlementResources(player)) {
				if (getState() == State::FIRST_BUILDS) {
					if (validFirstSettlement(coords, player)) {
						return true;
					}
				}
				else {
					if (isValidSettlement(coords, player)) {
						return true;
					}
				}
			}
			else {
				if (getState() == State::FIRST_BUILDS) {
					if (validFirstSettlement(coords, player)) {
						return true;
					}
				}
			}
			break;
		case BuildingType::ROAD:
			if (hasRoadResources(player)) {
				if (isValidRoad(coords, player)) {
					return true;
				}
			}
			else if (getState() == State::FIRST_BUILDS) {
				if (isValidRoad(coords, player)) {
					return true;
				}
			}
			break;
		case BuildingType::CITY:
			if (hasCityResources(player)) {
				if (isValidCity(coords, player)) {
					return true;
				}
			}
			break;
	}

	return false;
}

void
CatanGame::buildRoad(Building* building, Coord coords, PlayerId playerID)
{

	/*
	* Busco un camino de entre las fichas del jugador y 
	* lo configuro para conectarrlo al building dado, en ambos
	* sentidos
	*/
	Building* newRoad = getPlayer(playerID)->popRoad();
	newRoad->addNeighbour(building);
	building->addNeighbour(newRoad);
	
	/*
	* Agrego la ficha al tablero del mapa de construcciones realizadas
	* y configuro los puntos del jugador 
	*/
	catanMap->build(newRoad, coords);
	getPlayer(playerID)->addPoints(ROAD_BUILT_POINTS);
	setInfo("[CatanGame] Un nuevo Road ha sido colocado!");

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
	Building* newCity = getPlayer(playerID)->popCity();
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
	catanMap->demolish(building);
	catanMap->build(newCity, coords);
	getPlayer(playerID)->giveBackBuilding(building);
	getPlayer(playerID)->removePoints(SETTLEMENT_BUILT_POINTS);
	getPlayer(playerID)->addPoints(CITY_BUILT_POINTS);
	setInfo("[CatanGame] Una nueva ciudad ha sido colocada!");

	/* Actualizo los puntos y veo ganador */
	updateWinner();
}

void
CatanGame::buildSettlement(Building* building, Coord coords, PlayerId playerID)
{
	/* Extraigo un asentamiento entre las fichas del jugador para luego
	* agregar las conexiones entre el anterior y este, ademas de su ubicacion
	*/
	Building* newSettlement = getPlayer(playerID)->popSettlement();
	if (building) {
		newSettlement->addNeighbour(building);
		building->addNeighbour(newSettlement);
	}

	/*
	* Agrego la nueva construccion al tablero y le asigno el puntaje
	*/
	catanMap->build(newSettlement, coords);
	getPlayer(playerID)->addPoints(SETTLEMENT_BUILT_POINTS);
	setInfo("[CatanGame] Un nuevo Settlement ha sido colocado!");

	/* Actualizo los docks disponibles del usuario/jugador */
	updateDocks(coords, playerID);

	/* Actualizo los puntos y veo ganador */
	updateWinner();
}

void
CatanGame::payRoad(PlayerId playerID) {
	Player* player = getPlayer(playerID);
	returnCards(player->giveCards(ResourceId::HILL, ROAD_BRICK_NEEDED));
	returnCards(player->giveCards(ResourceId::FOREST, ROAD_LUMBER_NEEDED));
}

void
CatanGame::payCity(PlayerId playerID) {
	Player* player = getPlayer(playerID);
	returnCards(player->giveCards(ResourceId::MOUNTAIN, CITY_ORE_NEEDED));
	returnCards(player->giveCards(ResourceId::FIELD, CITY_GRAIN_NEEDED));
}

void
CatanGame::paySettlement(PlayerId playerID) {
	Player* player = getPlayer(playerID);
	returnCards(player->giveCards(ResourceId::HILL, SETTLEMENT_BRICK_NEEDED));
	returnCards(player->giveCards(ResourceId::FOREST, SETTLEMENT_LUMBER_NEEDED));
	returnCards(player->giveCards(ResourceId::PASTURES, SETTLEMENT_WOOL_NEEDED));
	returnCards(player->giveCards(ResourceId::FIELD, SETTLEMENT_GRAIN_NEEDED));
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

	setInfo("[CatanGame] Ningun muelle acepta esa cantidad de cartas!");
	return false;
}

bool
CatanGame::isValidPlayerExchange(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID) {

	/*
	* Verifico que ambos jugadores tengan las cartas disponibles
	* para poder realizar el intercambio, y ademas, verifico que la cantidad
	* no se pase del maximo valor de transacciones posibles
	*/
	if (offeredCards.size() > 9 || requestedCards.size() > 9) {
		setInfo("[CatanGame] Maximo de cartas para intercambios superado!");
		return false;
	}

	if (canPlayerAccept(offeredCards, srcPlayerID) && canPlayerAccept(requestedCards, (OPONENT_ID(srcPlayerID)))) {
		return true;
	}
	else {
		setInfo("[CatanGame] No es posible realizar ese intercambio.");
		return false;
	}
}

bool
CatanGame::isValidBankExchange(list<ResourceId>& offeredCards, PlayerId playerID) {

	if (accepts(offeredCards, BANK_TRANSACTION_CARDS_COUNT) && canPlayerAccept(offeredCards, playerID)) {
		return true;
	}
	else {
		setInfo("[CatanGame] Transaccion con el Banco invalida! Revise cantidad y tipo de cartas.");
		return false;
	}
}

bool
CatanGame::canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID)
{
	/*
	* Verifico que la cantidad de recursos de cada tipo que el jugador tiene
	* sea superior o equivalente a la cantidad en la lista de cartas que se piden
	*/
	return	(
			(getPlayer(destPlayerID)->getResourceCount(ResourceId::FOREST) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::FOREST)) &&
			(getPlayer(destPlayerID)->getResourceCount(ResourceId::HILL) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::HILL)) &&
			(getPlayer(destPlayerID)->getResourceCount(ResourceId::MOUNTAIN) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::MOUNTAIN)) &&
			(getPlayer(destPlayerID)->getResourceCount(ResourceId::FIELD) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::FIELD)) &&
			(getPlayer(destPlayerID)->getResourceCount(ResourceId::PASTURES) >= (unsigned int)std::count(requestedCards.begin(), requestedCards.end(), ResourceId::PASTURES))
			);
}

void
CatanGame::Exchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID)
{
	/*
	* Para realizar un intercambio de este tipo, primero se remueven todas las cartas
	* dadas por el jugador de su pilon, y luego se agrega la carta pedida, creandola
	* previamente
	*/
	returnCards(getPlayer(playerID)->giveCards(offered));

	/*
	* Creo la carta pedida y se la entrego al jugador en cuestion
	*/
	getPlayer(playerID)->addCard(takeCards(wanted, 1));
	setInfo("[CatanGame] Intercambio de cartas realizado exitosamente!");
}

void
CatanGame::playerExchange(list<ResourceId>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID)
{
	PlayerId oponent = OPONENT_ID(srcPlayerID);
	/*
	* Primero busco todas las cartas ofrecidas por el jugador y tomo cada una de ellas,
	* luego la modifico y la entrego al otro jugador, verificando el contenido de la misma
	*/
	getPlayer(oponent)->addCard(getPlayer(srcPlayerID)->giveCards(offered));

	/*
	* Busco las cartas del segundo jugador, las cuales primero modifico, y luego quito y entrego
	* al que las recibe
	*/
	getPlayer(srcPlayerID)->addCard(getPlayer(oponent)->giveCards(wanted));
	setInfo("[CatanGame] Intercambio de cartas realizado exitosamente!");
}

void
CatanGame::pass() {
	this->turn = OPONENT_ID(this->turn);
	setInfo("[CatanGame] Ha pasado de turno.");
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
	if (localPlayer->getVictoryPoints() == WINNER_POINTS) {
		winner = PlayerId::PLAYER_ONE;
		setInfo("[CatanGame] ENHORABUENA, has ganado la partida!");
	}
	else if (remotePlayer->getVictoryPoints() == WINNER_POINTS) {
		winner = PlayerId::PLAYER_TWO;
		setInfo("[CatanGame] UUUF CASI! La proxima sera campeon, perdiste...");
	}
}