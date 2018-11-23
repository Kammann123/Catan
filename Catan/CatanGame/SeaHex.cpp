#include "SeaHex.h"

SeaHex::
SeaHex(unsigned char coord, SeaId dockOne, SeaId dockTwo)
{
	/* Inicializacion */
	this->coord = coord;
	this->dockList.push_back(dockOne);
	this->dockList.pus
}

unsigned char
SeaHex::getCoord(void) const {
	return this->coord;
}

SeaId
SeaHex::getType(void) const {
	return this->seaId;
}