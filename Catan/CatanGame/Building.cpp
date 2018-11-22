#include "Building.h"

Building::
Building(PlayerId player, BuldingType type)
{
	this->player = player;
	this->type = type;
}

string Building::
getPlace(void)
{
	return place;
}

PlayerId Building::
getPlayer(void)
{
	return player;
}

BuldingType Building::
getType(void)
{
	return type;
}

void Building::
setPlace(string place)
{
	this->place = place;
}