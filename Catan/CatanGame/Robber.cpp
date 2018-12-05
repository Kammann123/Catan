#include "Robber.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"
#include "CatanMap.h"

Robber::
Robber(CatanMap* map) : MouseUI(ROBBER_ID, 0, 0, true) {
	this->map = map;
	this->setUIDestroy(false);
}

Robber::
Robber(CatanMap* map, Coord coord) : MouseUI(ROBBER_ID, 0, 0, true) {
	this->map = map;
	this->coord = coord;
}

Coord
Robber::getCoord(void)  const {
	return this->coord;
}

void
Robber::move(Coord coord, double x, double y) {
	this->coord = coord;
	this->setPosition(x - width / 2, y - height / 2);
}

void
Robber::refactor(void) {
	map->moveRobber(this->coord);
}