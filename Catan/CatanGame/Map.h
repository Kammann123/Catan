#pragma once

enum BuldingType { SETTLEMENT, ROAD, CITY };
#include <string>
#include "Player.h"
using namespace std;
class ResourceHex {

};
class Building {

public:
	Building(PlayerId player, BuldingType type);
	string getPlace();
	PlayerId getPlayer();
	BuldingType getType();
	void setPlace(string place);
private:
	string place;
	BuldingType type;
	PlayerId player;

};