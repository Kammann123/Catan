#include "Robber.h"

Robber::
Robber() {
	this->coord = 'Z';
}

Robber::
Robber(unsigned char coord) {
	this->coord = coord;
}

void 
Robber::setCoord(unsigned char coord) {
	this->coord = coord;
}

unsigned char
Robber::getCoord(void) const {
	return this->coord;
}