#include "Player.h"
#include "Building.h"

Building::
Building(PlayerId player, BuildingType type)
{
	this->player = player;
	this->type = type;
	this->place = "FFF"; // el string "FFF" significa posición no asignada
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

BuildingType Building::
getType(void)
{
	return type;
}

void Building::
setPlace(string place)
{
	this->place = place;
}