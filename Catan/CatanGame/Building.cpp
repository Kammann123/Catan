#include "Player.h"
#include "Building.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

Building::
Building(Player* player, BuildingType type) : MouseUI(BUILDING_ID, 0, 0, true) {
	this->setUIDestroy(false);
	this->player = player;
	this->type = type;
	this->neighbours.clear();
	this->built = false;
	this->visited = false;
	this->angle = 90;
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
	this->setPosition(x - width / 2, y - height / 2);
	this->setAngle(radian);
	this->setEnable(false);
	((MouseUI*)this)->setStatus(MouseUI::Status::IDLE);
}

void
Building::demolish(void) {
	/* Configuro la remocion de la construccion */
	this->built = false;
	this->setEnable(true);
	refactor();
}

void
Building::refactor(void) {
	if (!built){

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
		this->setPosition(value.x + player->xPos(), value.y + player->yPos());
		this->setAngle(value.info);
	}
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

bool 
Building::isHead(void) {
	/* Se agrega logica para determinar si el nodo del grafo
	* es un cabeza del mismo, para determinar si los recorridos
	* se comienzan desde aqui
	*/
	if (coord.isDot()) {
		return neighbours.size() == 1;
	}
	else {

		/* Creo las dos listas de cada lado del road, para clasificar
		* sus vecinos a medida que los busco a cada uno de ellos  */
		list<Building*> firstSide;
		list<Building*> secondSide;

		for (Building* neighbour : neighbours) {
			/* Verifico que no esten inicialmente vacios las listas
			* que clasifican los buildings segun lados */
			if (firstSide.empty() && secondSide.empty()) {
				firstSide.push_back(neighbour);
				continue;
			}

			/* Me fijo a cual de los dos lados pertenece el nuevo vecino
			* y cuando lo logro determinar, lo agrego a cada uno de esos
			* lados */
			if (isBuildingSide(firstSide, neighbour)) {
				firstSide.push_back(neighbour);
			}
			else if (isBuildingSide(secondSide, neighbour)) {
				secondSide.push_back(neighbour);
			}
			else if( secondSide.empty() ){
				secondSide.push_back(neighbour);
			}

			/* Si detecto que se agruparon vecinos a ambos lados, entonces
			* no es un head, es decir, la punta de camino */
			if (firstSide.size() && secondSide.size()) {
				return false;
			}
		}

		/* Si nunca detecte vecinos a ambos lados... es punta de camino! */
		return true;
	}
}

bool
Building::isBuildingSide(list<Building*> side, Building* building) {
	for (Building* sideBuilding : side) {
		if (sideBuilding->getPlace().isEdgeOf(building->getPlace())) {
			return true;
		}
		else if (sideBuilding->getPlace().edgeContinuity(building->getPlace())) {
			return true;
		}
	}
	return false;
}

bool 
Building::cutsRoad(Building* building) {

	/* Me fijo, si soy un Building de tipo Road, pues
	* mi coordenada es Edge, entonces puedo verificar si
	* este Building, que debe ser City o Settlement,
	* puede cortarme la secuencia */
	if (coord.isEdge()) {

		/* Verifico si existe algun neighbour (vecino) que sea Edge
		* con el cual se forme continuidad desde este edge, y obviamente
		* se vea cortado por el building */
		for (Building* neighbour : neighbours) {

			if (neighbour->getPlace().isEdge()) {
				if (coord.isEdgeOf(building->getPlace()) && neighbour->getPlace().isEdgeOf(building->getPlace())) {

					/* Corto el camino. */
					removeNeighbour(neighbour);
					neighbour->removeNeighbour(this);
					return true;
				}
			}
		}
	}
	return false;
}