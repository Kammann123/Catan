#pragma once

#include "Robber.h"
#include "Player.h"
#include "Building.h"
#include "ResourceHex.h"
#include "ResourceCard.h"
#include "SeaHex.h"
#include "CatanStatus.h"
#include "Coord.h"
#include "CatanState.h"

#include "../MVC/Subject.h"
#include "../CatanEvents/CatanEvent.h"
#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

#include <list>
#include <map>
#include <deque>
#include <iterator>

/* Docks requierements */
#define NORMAL_COUNT	3
#define WHEAT_COUNT		2
#define SHEEP_COUNT		2
#define BRICK_COUNT		2
#define STONE_COUNT		2
#define WOOD_COUNT		2

/* Map assignments */
#define HILL_HEX_COUNT		3
#define FOREST_HEX_COUNT	4
#define	MOUNTAIN_HEX_COUNT	3
#define FIELD_HEX_COUNT		4
#define PASTURE_HEX_COUNT	4

/* Transaction definitions */
#define BANK_TRANSACTION_CARDS_COUNT 4 

/* Buildings requirements */
#define SETTLEMENT_BRICK_NEEDED		1
#define SETTLEMENT_LUMBER_NEEDED	1
#define SETTLEMENT_WOOL_NEEDED		1
#define SETTLEMENT_GRAIN_NEEDED		1

#define CITY_ORE_NEEDED		3
#define CITY_GRAIN_NEEDED	2

#define ROAD_BRICK_NEEDED	1
#define ROAD_LUMBER_NEEDED	1

/* Robber definitions */
#define ROBBER_CARDS_COUNT	7

/* Longest road definitions */
#define MIN_LONGEST_ROAD	5
#define LONGEST_ROAD_POINTS	2

/* Victory Points reference */
#define ROAD_BUILT_POINTS			0
#define SETTLEMENT_BUILT_POINTS		1
#define CITY_BUILT_POINTS			2

#define RANDOM_DICE	((rand() % 6) + 1)

#define OPONENT_ID(id)	(id == PlayerId::PLAYER_ONE ? PlayerId::PLAYER_TWO : PlayerId::PLAYER_ONE)


using namespace std;

/*
* CatanGame
* Se definen las reglas del juego y la clase con la informacion sobre la partida actual
* asi como el Modelo para la implementacion de MVC y luego el Context para el State pattern.
*
* Consideraciones:
*	+ Se define como PLAYER_ONE al jugador local y PLAYER_TWO al oponente.
*
*/
class CatanGame : public Subject{
public:

	/* Constructor y destructor */
	CatanGame(string localPlayerName);
	CatanGame();
	~CatanGame();

	/*
	* handle
	* Metodo que permite ejecutar un evento sobre la logica del juego
	*/
	void handle(NetworkPacket* packet);
	void handle(CatanEvent* event);

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

	CatanState* getCurrentState(void);
	CatanState* getPrevState(void);

public:

	/* 
	* Metodos para la interfaz con el CatanNetworking, para garantizar
	* acceso a configurar y pedir datos del CatanGame momento a momento.
	* Tambien su uso esta disponible para CatanGui.
	*/
	bool isRobberStatus(void);

	void setRemoteName(string remoteName);

	PlayerId getTurn(void);
	string getLocalName(void);
	map<Coord, MapValue> getMap(void);
	map<Coord, unsigned char> getTokens(void);

private:

	/*
	* getPlayer
	* Permite obtener el objeto Player en funcion del id con el cual
	* se determina el turno actual del juego o bien una accion realizada.
	*/
	Player& getPlayer(PlayerId playerId);

public:

	/*
	* Aclaracion importante, a continuacion se declaran los metodos empleados
	* para validar acciones y ejecutar acciones del juego, sin control logico
	* de flujo. Se las coloca ordenadas y clasificadas segun partes del juego.
	*/

	/*
	* resetGame
	* Reinicia el juego volviendo a sus valores iniciales
	* las variables de interes, como los puntos, etc...
	*
	* Unicamente reinicia las variables del juego, no define ninguna nueva
	* disposicion de recursos ni nada por el estilo, de ello se encargan
	* otras partes.
	*/
	void resetGame(void);

	/* 
	* Metodos de generacion inicial del juego bajo las reglas
	* definidas en Catan. Se puede generar el mapa seteando los
	* recursos en un orden determinado. Se puede generar el oceano
	* en un orden de muelles determinado. Y se puede generar los valores
	* aleatorios de tokens asignados para cada Token.
	*/
	void generateMap(void);
	void generateTurn(void); 
	void generateOcean(void);
	void generateTokens(void);

	/*
	* Metodos para la validacion de los elementos de juego, como
	* seran los mapas, tanto de tierra como mar y los valores de
	* tokens asignados a ellos.
	*/
	bool verifyMap(map<Coord, MapValue> landMap);
	bool verifyTokens(map<Coord, unsigned char> tokens);

	/*
	* assignResources
	* Al notificar un valor de dados jugados, el juego asigna
	* correspondientemente a cada jugar los recursos que reciben
	* segun el numero y los settlements como debe ser.
	*/
	void assignResources(unsigned int dices);
	void assignResources(PlayerId player, ResourceId resource, unsigned int qty);

	/*
	* updateLongestRoad
	* Actualiza el estado actual del longest road.
	*/
	void updateLongestRoad(void);
	void getLongestRoad(Building* building, unsigned int length = 0);

	/*
	* hasRobberCards
	* Permite ver si un jugador dado cumple las condiciones en cuanto
	* a cantidad de recursos acumulados, para ver si debe descartar
	* alguna de esas cartas, con lo cual, es true si se valida esto.
	*/
	bool hasRobberCards(PlayerId playerID);
	
	/*
	* robberCards
	* Un jugador dado entrega una lista de recursos que utilizan
	* para tomar y descartar esas cartas del mismo jugador.
	* Aclaracion, la seleccion es por tipo de recurso.
	*/
	void robberCards(list<ResourceCard*>& cards, PlayerId playerID);
	void robberCards(list<ResourceId>& cards, PlayerId playerID);

	/*
	* moveRobber
	* Permite mover el robber a una nueva ubicacion dentro del mapa.
	*/
	void moveRobber(Coord newCoords);

	/*
	* updateDocks
	* Mantengo actualizado el conjunto de docks disponibles que tiene 
	* cada uno de los jugadores durante la partida.
	*
	* Presupone que coord debe ser un settlement o city, no obstante
	* lo validara para verificar antes que sea un dock.
	*/
	void updateDocks(Coord coord, PlayerId playerId);

	/*
	* isValidRoad,isValidCity,isValidSettlement
	* Validan la colocacion de cada una de esas construcciones para un jugador
	* determinado, en la ubicacion dada, verificando que sea posible a nivel constructivo,
	* esto quiere decir, que no valida requisitos economicos, unicamente si es posible,
	* ya que puede haber una construccion en esa ubicacion, o no cumplir las reglas del juego.
	*
	* Devuelven puntero nullptr si no cumple, o devuelve puntero a los building de interes
	* donde en caso de Road y Settlement seran contiguos o bien en caso de City, el settlement
	* a sustituir.
	*/
	Building* isValidRoad(Coord coords, PlayerId playerID);
	Building* isValidCity(Coord coords, PlayerId playerID);
	Building* isValidSettlement(Coord coords, PlayerId playerID);

	/*
	* hasCityResources, hasSettlementResources, hasRoadResources
	* Validan la disponibilidad de los recursos de un player para realizar 
	* algunas de esas construcciones, esto quiere decir, si cumple los requisitos
	* economicos para realizar tal construccion.
	*/
	bool hasCityResources(PlayerId playerID);
	bool hasSettlementResources(PlayerId playerID);
	bool hasRoadResources(PlayerId playerID);
	
	/*
	* buildRoad, buildCity, buildSettlement
	* Realizan la construccion de alguna de esas entidades en la posicion definida
	* por el usuario, para ese jugador, donde se asume previa validacion ya que 
	* consiste unicamente en el proceso de cobrar recursos y ubicar la entidad.
	*
	* El requisito de un puntero a Building es para la conexion de las construcciones
	* en caso de City, el reemplazo del settlement.
	*/
	void buildRoad(Building* building, Coord coords, PlayerId playerID);
	void buildCity(Building* building, Coord coords, PlayerId playerID);
	void buildSettlement(Building* building, Coord coords, PlayerId playerID);

	/*
	* dockAccepts
	* Validan si el muelle en cuestion acepta el conjunto de cartas dado
	* a modo de intercambio, cumpliendo las reglas respectivas de cada uno de ellos
	*/
	bool dockAccepts(list<ResourceId>& cards, unsigned int qty, ResourceId id);
	bool dockAccepts(list<ResourceId>& cards, unsigned int qty);
	bool dockAccepts(list<ResourceCard*>& cards, unsigned int qty, ResourceId id);
	bool dockAccepts(list<ResourceCard*>& cards, unsigned int qty);

	/*
	* isValidDockExchange, isValidPlayerExchange, isValidBankExchange
	* Valida intercambios de cartas realizados u ofrecidos por algun jugador, ya sea con otro jugador, como tambien con
	* alguno de los muelles o bien el banco del juego. Estas validaciones implican verificar que sea posible la transaccion
	* , que tenga los recursos para hacerla, y que tenga disponible las opciones de hacerla, por los muelles por ejemplo.
	*/
	bool isValidDockExchange(list<ResourceId>& offeredCards, PlayerId playerId);
	bool isValidDockExchange(list<ResourceCard*>& offeredCards, PlayerId playerId);
	bool isValidPlayerExchange(list<ResourceCard*>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID);
	bool isValidPlayerExchange(list<ResourceId>& offeredCards, list<ResourceId>& requestedCards, PlayerId srcPlayerID);
	bool isValidBankExchange(list<ResourceCard*>& offeredCards, PlayerId playerID);

	/*
	* canPlayerAccept
	* Este metodo permite determinar si es valido que el jugador acepte el intercambio de cartas
	* con lo garantiza si se da o no la opcion de aceptarla. Verifica que disponga las cartas...
	*/
	bool canPlayerAccept(list<ResourceId>& requestedCards, PlayerId destPlayerID);
	bool canPlayerAccept(list<ResourceCard*> requestedCards, PlayerId destPlayerID);

	/*
	* bankExchange, playerExchange, dockExchange
	* Realizan los intercambios de cartas entre un jugador y, ya sea otro jugador o bien
	* el banco o un muelle, donde se asume validacion y unicamente se distribuyen recursos.
	*/
	void Exchange(list<ResourceCard*>& offered, ResourceId wanted, PlayerId playerID);
	void Exchange(list<ResourceId>& offered, ResourceId wanted, PlayerId playerID);
	void playerExchange(list<ResourceCard*>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID);
	void playerExchange(list<ResourceId>& offered, list<ResourceId>& wanted, PlayerId srcPlayerID);

	/*
	* pass
	* Ejecuta la accion de pasar de turno
	*/
	void pass(void);

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

private:
	
	/* Rutinas bajo nivel de inicializacion o restablecimiento */
	void _init_game(void);

	void _free_buildings(void);
	void _free_events(void);
	void _free_states(void);

	void _clear_resource_map(void);
	void _clear_sea_map(void);

	void _notify_change(void);

private:
	
	Player localPlayer;
	Player remotePlayer;
	list<Building*> builtMap;
	map<Coord, ResourceHex> resourceMap;
	map<Coord, SeaHex> seaMap;
	PlayerId turn;
	PlayerId longestRoad;
	Robber robber;

	deque<CatanEvent*> eventQueue;

	CatanState* state;
	CatanState* prevState;

private:
	
	map<PlayerId, unsigned int> playerLongestRoad;
	map<PlayerId, list<SeaId>> playerDocks;
};