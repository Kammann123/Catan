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