#pragma once

#include <string>
#include <list>
#include "ResourceCard.h"
#include "Map.h"

using namespace std;

enum PlayerId : unsigned int {PLAYER_ONE, PLAYER_TWO};

class Player {
public:
	Player(string name, unsigned int settleCount, unsigned int citiesCount, unsigned int roadsCount);
	string getName(void);
	unsigned int getVictoryPoints(void);
	list <ResourceCard *> * getResourceCards();
	void addPoints(unsigned int points = 0);
	void removePoints(unsigned int points = 0);
	void addResourceCard(ResourceCard * card);
	void removeResourceCard(ResourceCard * card);
	bool hasRoad(void);
	bool hasSettlements(void);
	bool hasCities(void);
	Building* popRoad(void);
	Building* popSettlement(void);
	Building* popCity(void);
private:
	string name;
	unsigned int victoryPoints;
	list<ResourceCard * > resourceCards;
	list<Building*> settlements;
	list<Building*> cities;
	list<Building*> roads;

};