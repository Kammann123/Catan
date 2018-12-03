#pragma once

#include "ResourceCard.h"
#include "Building.h"

#include "../CatanGui/AllegroUI/ContainerUI.h"

#include <string>
#include <list>

#define SETTLEMENT_COUNT	5
#define CITY_COUNT			4
#define ROAD_COUNT			15

using namespace std;

enum class PlayerId : int {PLAYER_ONE, PLAYER_TWO, PLAYER_NONE};

class CatanGame;

class Player : public ContainerUI {
public:
	/*
	* Constructor
	*/
	Player(PlayerId player, CatanGame* game);
	~Player();

	void setName(string name);

	/*
	* getters - Permite lectura de informacion del jugador
	*/
	unsigned int getResourceCount(ResourceId resourceID) const;
	list<Building*> buildings(BuildingType type);
	unsigned int getResourceCount(void) const;
	unsigned int getVictoryPoints(void);
	list<ResourceCard*> showCards(void);
	unsigned int hasSettlements(void);
	unsigned int hasCities(void);
	unsigned int hasRoads(void);
	string getName(void);

	/********************************
	* Interfaz de manejo del puntaje
	********************************/
	void removePoints(unsigned int points = 0);
	void addPoints(unsigned int points = 0);
	void resetVictoryPoints(void);

	/******************************
	* Interfaz de manejo de cartas
	******************************/
	list<ResourceCard*> giveCards(ResourceId id, unsigned int qty);
	ResourceCard* giveCard(ResourceId id);

	void removeCard(list<ResourceCard*> cards);
	void removeCard(ResourceCard* card);

	void addCard(list<ResourceCard*> cards);
	void addCard(ResourceCard * card);

	/***************************************
	* Interfaz de manejo de construcciones
	***************************************/
	void giveBackBuilding(Building* building);
	Building* popSettlement(void);
	Building* popRoad(void);
	Building* popCity(void);

private:

	/*******************************************
	* Metodos de construccion, inicializacion y 
	* destruccion de los miembros del Player
	********************************************/
	void _create_settlements(void);
	void _create_roads(void);
	void _create_cities(void);

	void _destroy_settlements(void);
	void _destroy_roads(void);
	void _destroy_cities(void);
	void _destroy_cards(void);

private:
	PlayerId player;
	string name;
	unsigned int victoryPoints;

	list<ResourceCard*> resourceCards;
	list<Building*> settlements;
	list<Building*> cities;
	list<Building*> roads;

	CatanGame* game;
};