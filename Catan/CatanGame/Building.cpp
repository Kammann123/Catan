#include "Player.h"
#include "Building.h"

Building::
Building(Coord place, PlayerId player, BuildingType type) {
	this->place = place;
	this->player = player;
	this->type = type;
}

Building::
Building(PlayerId player, BuildingType type) {
	this->place = BUILDING_NOT_PLACED;
	this->player = player;
	this->type = type;
}

Building::
Building(BuildingType type) {
	this->place = BUILDING_NOT_PLACED;
	this->player = PlayerId::PLAYER_NONE;
	this->type = type;
}

Coord Building::
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
setPlace(Coord place)
{
	this->place = place;
}

void Building::
setPlayer(PlayerId player) {
	this->player = player;
}