#include "SeaHex.h"

SeaHex::
SeaHex(unsigned char coord, SeaId dockOne, SeaId dockTwo)
{
	/* Inicializacion */
	this->coord = coord;
	this->dockList.push_back(dockOne);
	this->dockList.push_back(dockTwo);
}

SeaHex::
SeaHex(unsigned char coord, SeaId onlyDock)
{
	/* Inicializacion */
	this->coord = coord;
	this->dockList.push_back(onlyDock);
}


unsigned char
SeaHex::getCoord(void) const {
	return this->coord;
}

SeaId
list<SeaId> getDockList(void) const
{
	return this->dockList;
}