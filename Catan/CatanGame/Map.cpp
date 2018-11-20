#include "Map.h"

Building::Building(PlayerId player, BuldingType type)
{
	this->player = player;
	this->type = type;
}

string Building::getPlace()
{
	return place;
}

PlayerId Building::getPlayer()
{
	return player;
}

BuldingType Building::getType()
{
	return type;
}

void Building::setPlace(string place)
{
	this->place = place;
}
