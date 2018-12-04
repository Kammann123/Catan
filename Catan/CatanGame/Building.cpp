#include "Player.h"
#include "Building.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

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
Building::build(Coord coord, double x, double y, double radian) {
	/* Configuro los valores del building para construirlo */
	this->built = true;
	this->coord = coord;
	this->setPosition(x, y);
	this->setAngle(radian);
}

void
Building::demolish(void) {
	/* Configuro la remocion de la construccion */
	this->built = false;

	/* Determino que tipo de construccion es, para buscar
	* el id correspondiente dentro del container de player
	* y lo busco, obteniendo la informacion de la nueva posicion
	*/
	string index;
	switch (this->type) {
		case BuildingType::SETTLEMENT:
			index = POSITION_SETTLEMENT;
			break;
		case BuildingType::ROAD:
			index = POSITION_ROAD;
			break;
		case BuildingType::CITY:
			index = POSITION_CITY;
			break;
	}
	container_t value = (*player)[index];
	this->setPosition(value.x, value.y);
	this->setAngle(value.info);
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