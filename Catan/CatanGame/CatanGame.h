#pragma once

#include "Robber.h"
#include "Player.h"
#include "Building.h"
#include "ResourceHex.h"
#include "ResourceCard.h"
#include "SeaHex.h"
#include "CatanStatus.h"
#include "CatanState.h"

#include "../CatanEvents/CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

#include <list>
#include <map>
#include <deque>

#define BANK_TRANSACTION_CARDS_COUNT 4 

#define SETTLEMENT_BRICK_NEEDED 1
#define SETTLEMENT_LUMBER_NEEDED 1
#define SETTLEMENT_WOOL_NEEDED 1
#define SETTLEMENT_GRAIN_NEEDED 1

#define CITY_ORE_NEEDED 3
#define CITY_GRAIN_NEEDED 2

#define ROAD_BRICK_NEEDED 1
#define ROAD_LUMBER_NEEDED 1

#define ROBBER_CARDS_COUNT 7


using namespace std;

/*
* CatanGame
* Clase con la logica y la informacion de la partida actual
* del juego Catan.
* El funcionamiento del flujo de la logica del CatanGame se basa
* en el patron de diseño State, siendo el CatanGame el Context
* o Wrapper de los estados.
*/
class CatanGame {
public:

	/* Definimos estados del catan game */
	enum States : CatanState::Type {};

	/* Constructor y destructor */
	CatanGame(string localPlayerName);
	CatanGame();
	~CatanGame();

	/*
	* handle
	* Metodo que permite ejecutar un evento sobre la logica del juego
	*/
	CatanStatus handle(NetworkPacket* packet);
	CatanStatus handle(CatanEvent* event);

	/* Getters */
	Player& getLocalPlayer(void);
	Player& getRemotePlayer(void);
	list<Building*>& getBuiltMap(void);
	map<unsigned char, ResourceHex> getResourceMap(void);
	map<unsigned char, SeaHex> getSeaMap(void);
	PlayerId getTurn(void);
	PlayerId getLongestRoad(void);
	Robber getRobber(void);
	CatanState* getCurrentState(void);
	CatanState* getPrevState(void);

	/*
	* getNextEvent
	* Devuelve un evento en la cola
	*/
	CatanEvent* getNextEvent(void);

	/*
	* hasEvents
	* Devuelve si hay eventos en la cola
	*/
	bool hasEvents(void) const;

	/*
	* changeState
	* Cambia de estado el context CatanGame
	*/
	void changeState(CatanState* newState);

private:

	friend class CatanState; // no funcoina!!1

	/* Generación de juego */

	void generateMap(void); // ver reglas de creación
	void generateOcean(void); // idem anterior
	void generateTokens(void); // numeros que van encima de los hexagonos



	/* Acciones de juego */

	void assignResources(unsigned int dices);
	void robberCards(list<ResourceId>& cards, PlayerId playerID);
	void moveRobber(unsigned char newCoords);
	
	void buildRoad(string coords, PlayerId playerID);
	void buildCity(string coords, PlayerId playerID);
	void buildSettlement(string coords, PlayerId playerID);

	/*
	* pass()
	* Método que pasa el turno al otro jugador
	*/

	void pass(void);

	void bankExchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID);
	void playerExchange(list<ResourceId>& offered, list<ResourceId> wanted, PlayerId srcPlayerID);
	void dockExchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID);









	/* VALIDACION DE MOVIMIENTOS */


	bool hasRobberCards(PlayerId playerID); // chequea si tiene mas de 7 cartas, para descartar
	/*
	* isValidxxxxx()
	* Métodos que nos informan si es válida la construcción de un road, city o settlement, respectivamente (GEOGRAFICO).
	*/

	bool isValidRoad(string coords, PlayerId playerID);
	bool isValidCity(string coords, PlayerId playerID);
	bool isValidSettlement(string coords, PlayerId playerID);

	/*
	* hasXxxResources()
	* Métodos que nos informan si es válida la construcción de un road, city o settlement, respectivamente (RECURSOS).
	*/
	
	bool hasRoadResources(PlayerId playerID);
	bool hasCityResources(PlayerId playerID);
	bool hasSettlementResources(PlayerId playerID);



	/*
	* isValidDockTransaction()
	* Verifica que la transacción propuesta sea coherente en el marco del juego (devuelve true si lo es, false  en caso contrario)
 	*/
	bool isValidDockTransaction(list<ResourceId>& offeredCards,ResourceId requestedCard, unsigned char seaCoord,unsigned char dockNumber,PlayerId player);
	bool isValidPlayerTransaction(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID);
	bool isValidBankTransaction(list<ResourceId>& offeredCards, PlayerId playerID);

	/*
	* isAvailableDock()
	* Verifica si el puerto está disponible para una transacción
	*/

	bool isAvailableDock(SeaId dockID, PlayerId playerID);

	
	/*
	* isValidListOfCards()
	* Devuelve true en el caso que las cartas ofrecidas estén disponibles para el jugador
	*/
	bool isValidListOfCards(list<ResourceId>& offeredCards, PlayerId playerID);

	/*
	* getResourceCount()
	* Devuelve la cantidad de resourceCards de un determinado tipo que tiene un jugador.
	*/
	unsigned int getResourceCount(list<ResourceId>& cardsList, ResourceId resourceID) const;
	unsigned int getResourceCount(list<ResourceCard*>& cardsList, ResourceId resourceID) const;

	/*
	* matchCoords()
	* Devuelve true en el caso de que las dos coordenadas hagan referencia al mismo lugar
	*/
	bool matchCoords(string str1, string str2);

	/*
	* addNewEvent
	* Agrega un nuevo evento a la cola
	*/
	void addNewEvent(NetworkPacket* packet);
	void addNewEvent(CatanEvent* event);

	/*
	* packetDispatcher
	* Devuelve evento a partir de un network packet
	*/
	CatanEvent* packetDispatcher(NetworkPacket* packet);

	Player localPlayer;
	Player remotePlayer;
	list<Building*> builtMap;
	map<unsigned char, ResourceHex> resourceMap;
	map<unsigned char, SeaHex> seaMap;
	PlayerId turn;
	PlayerId longestRoad;
	Robber robber;

	deque<CatanEvent*> eventQueue;

	CatanState* state;
	CatanState* prevState;
};