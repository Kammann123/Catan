#include "Player.h"
#include "Building.h"

Building::
Building(Player* player, BuildingType type) : MouseUI("", 0, 0, true) {
	this->player = player;
	this->type = type;
	this->neighbours.clear();
	this->built = false;
	this->visited = false;
}

bool
Building::isBuilt(void) {
	return built;
}

Coord 
Building::getPlace(void) {
	return coord;
}

Player*
Building::getPlayer(void) {
	return player;
}

BuildingType Building::
getType(void)
{
	return type;
}

void
Building::build(Coord coord, double x, double y) {
	this->built = true;
	this->coord = coord;
	this->setPosition(x, y);
}

void
Building::demolish(Coord coord, double x, double y) {
	this->build = false;
	this->coord = coord;
	this->setPosition(x, y);
}

void
Building::addNeighbour(list<Building*> buildings) {
	for (Building* building : buildings) {
		addNeighbour(building);
	}
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