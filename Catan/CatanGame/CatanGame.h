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

using namespace std;

/*
* CatanGame
* Clase con la logica y la informacion de la partida actual
* del juego Catan.
* El funcionamiento del flujo de la logica del CatanGame se basa
* en el patron de diseño State, siendo el CatanGame el Context
* o Wrapper de los estados.
*
* A saber de los ERRORES, unicamente CatanGame levanta errores de la logica
* que notifica a traves de su cola de eventos a sus observers, con lo cual
* cualquier error de los controllers es manejado por ellos.
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

	friend class CatanState;

	/* VALIDACION DE MOVIMIENTOS */

	/*
	* isValidxxxxx()
	* Métodos que nos informan si es válida la construcción de un road, city o settlement, respectivamente.
	*/

	bool isValidRoad(string coords, PlayerId playerID) const;
	bool isValidCity(string coords, PlayerId playerID) const;
	bool isValidSettlement(string coords, PlayerId playerID) const;

	/*
	* isValidDockTransaction()
	* Verifica que la transacción propuesta sea coherente en el marco del juego (devuelve true si lo es, false  en caso contrario)
 	*/
	bool isValidDockTransaction(list<ResourceCard*>& offeredCards,ResourceId requestedCard, unsigned char seaCoord,unsigned char dockNumber,PlayerId player);
	bool isValidPlayerTransaction(list<ResourceCard*>& offeredCards, list<ResourceCard*>& requestedCards, PlayerId srcPlayerID);
	bool isValidBankTransaction(list<ResourceCard*>& offeredCards, PlayerId playerID);

	/*
	* isAvailableDock()
	* Verifica si el puerto está disponible para una transacción
	*/

	bool isAvailableDock(SeaId dockID, PlayerId playerID);

	/*
	* isValidListOfCards()
	* Devuelve true en el caso que las cartas ofrecidas estén disponibles para el jugador
	*/
	bool isValidListOfCards(list<ResourceCard*>& offeredCards, PlayerId playerID);

	/*
	* getResourceCount()
	* Devuelve la cantidad de resourceCards de un determinado tipo que tiene un jugador.
	*/
	unsigned int getResourceCount(list<ResourceCard*>& cardsList, ResourceId resourceID) const;


	/*
	* addNewEvent
	* Agrega un nuevo evento a la cola
	*/
	void addNewEvent(NetworkPacket* packet);
	void addNewEvent(CatanEvent* event);

	/*
	* getPacketEvent
	* Devuelve evento a partir de un network packet
	*/
	CatanEvent* getPacketEvent(NetworkPacket* packet);

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