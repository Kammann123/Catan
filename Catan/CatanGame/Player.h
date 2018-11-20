#pragma once
#include <string>
#include <list>
#include "ResourceCard.h"
using namespace std;

enum PlayerId {PLAYER_ONE, PLAYER_TWO};
class Player {
public:
	Player(string name);
	string getName();
	unsigned int getVictoryPoints();
	list <ResourceCard *> * getResourceCards();
	void addPoints(unsigned int points = 0);
	void removePoints(unsigned int points = 0);
	void addResourceCard(ResourceCard * card);
	void removeResourceCard(ResourceCard * card);
private:
	string name;
	unsigned int victoryPoints;
	list <ResourceCard * > resourceCards;
	unsigned int settlements;
	unsigned int cities;
	unsigned int roads;

};