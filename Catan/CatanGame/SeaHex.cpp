#include "SeaHex.h"

SeaHex::
SeaHex(unsigned char coord, SeaId id) {

	/* Inicializacion */
	this->coord = coord;
	this->id = id;
}

unsigned char
SeaHex::getCoord(void) const {
	return this->coord;
}

SeaId
SeaHex::getType(void) const {
	return this->seaId;
}