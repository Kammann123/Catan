#include "Robber.h"

Robber::
Robber() {
	this->coord = 'Z';
}

Robber::
Robber(Coord coord) {
	this->coord = coord;
}

void 
Robber::setCoord(Coord coord) {
	this->coord = coord;
}

Coord
Robber::getCoord(void) const {
	return this->coord;
}