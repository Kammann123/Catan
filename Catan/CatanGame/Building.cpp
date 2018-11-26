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

void
Building::addNeighbour(Building* building) {
	neighbours.push_back(building);
}

void
Building::removeNeighbour(Building* building) {
	neighbours.remove(building);
}

void
Building::removeNeighbour(void) {
	neighbours.clear();
}

bool
Building::wasVisited(void) {
	return visited;
}

void
Building::visit(bool status) {
	visited = status;
}

list<Building*>
Building::getNeighbours(void) {
	return neighbours;
}

bool
Building::hasNeighbours(void) {
	return !neighbours.empty();
}