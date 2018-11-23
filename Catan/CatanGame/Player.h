#pragma once

#include "ResourceCard.h"
#include "Building.h"

#include <string>
#include <list>

#define SETTLEMENT_COUNT	5
#define CITY_COUNT			4
#define ROAD_COUNT			15

using namespace std;

enum class PlayerId : int {PLAYER_ONE, PLAYER_TWO};

class Player {
public:
	/*
	* Constructor
	*/
	Player(PlayerId player);
	Player(PlayerId player, string name, unsigned int settleCount, unsigned int citiesCount, unsigned int roadsCount);
	~Player();

	/*
	* getName()
	* Devuelve el nombre del jugador
	*/
	string getName(void);

	/*
	* setName
	* Establece el nombre
	*/
	void setName(string name);

	/*
	* getVictoryPoints()
	* Devuelve los puntos de victoria del jugador
	*/
	unsigned int getVictoryPoints(void);

	/*
	* getResourceCards()
	* Devuelve una lista con las resource cards del jugador
	*/
	list <ResourceCard *>& getResourceCards();

	/*
	* addPoints()
	* Suma puntos de victoria al jugador
	*/
	void addPoints(unsigned int points = 0);

	/*
	* removePoints()
	* Quita puntos de victoria al jugador
	*/
	void removePoints(unsigned int points = 0);

	/*
	* addResourceCard()
	* Añade una resource card al jugador
	*/
	void addResourceCard(ResourceCard * card);

	/*
	* removeResourceCard()
	* Quita una resource card del jugador
	*/
	void removeResourceCard(ResourceCard * card);

	/*
	* hasRoads()
	* Devuelve la cantidad de Roads disponibles
	*/
	unsigned int hasRoads(void);

	/*
	* hasSettlements()
	* Devuelve la cantidad de Settlementts disponibles
	*/
	unsigned int hasSettlements(void);

	/*
	* hasCities()
	* Devuelve la cantidad de Cities disponibles
	*/
	unsigned int hasCities(void);

	/*
	* popRoad()
	* Devuelve un objeto Road pre-creado
	*/
	Building* popRoad(void);

	/*
	* popSettlement()
	* Devuelve un objeto Settlement pre-creado
	*/
	Building* popSettlement(void);

	/*
	* popCity()
	* Devuelve un objeto City pre-creado
	*/
	Building* popCity(void);

private:
	PlayerId player;
	string name;
	unsigned int victoryPoints;
	list<ResourceCard*> resourceCards;
	list<Building*> settlements;
	list<Building*> cities;
	list<Building*> roads;
};