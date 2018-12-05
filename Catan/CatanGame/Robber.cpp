#include "Robber.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

Robber::
Robber() : MouseUI(ROBBER_ID, 0, 0, true) {
	this->setUIDestroy(false);
}

Robber::
Robber(Coord coord) : MouseUI(ROBBER_ID, 0, 0, true) {
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