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

string
SeaHex::getDockAbsCoords(SeaId dockID)
{
	if (dockList.size() == 1)
	{
		if (dockID == dockList[0])
		{
			return externCoords[coords*VERTEX_PER_SEA_PIECE + ONLY_DOCK_OFFSET];
		}
	}

	else
	{
		if (dockID == dockList[0])
		{
			return externCoords[coords*VERTEX_PER_SEA_PIECE + FIRST_DOCK_OFFSET];
		}

		else if (dockID == dockList[1])
		{
			return externCoords[coords*VERTEX_PER_SEA_PIECE + SECOND_DOCK_OFFSET];
		}
	}

	return "ERROR";

}
