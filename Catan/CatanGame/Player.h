#pragma once
#include <string>
#include <list>
#include "ResourceCard.h"
#include "Map.h"

using namespace std;

#define SETTLEMENTS_QTY	10
#define CITIES_QTY	10
#define ROADS_QTY	20

enum PlayerId {PLAYER_ONE, PLAYER_TWO};
class Player {
public:
	Player(string name, PlayerId id);
	~Player();
	string getName();
	unsigned int getVictoryPoints();
	list <ResourceCard *> * getResourceCards();
	void addPoints(unsigned int points = 0);
	void removePoints(unsigned int points = 0);
	void addResourceCard(ResourceCard * card);
	void removeResourceCard(ResourceCard * card);
	Building * getSettlement();
	Building * getCity();
	Building * getRoad();
private:
	PlayerId id;
	string name;
	unsigned int victoryPoints;
	list <ResourceCard * > resourceCards;
	list <Building * > settlements;
	list <Building * > cities;
	list <Building * > roads;

};