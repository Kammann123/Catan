#include "SeaHex.h"
#include "Coord.h"

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

SeaHex::
SeaHex(const SeaHex& copy) {
	this->coord = copy.coord;
	this->dockList = copy.dockList;
}

unsigned char
SeaHex::getCoord(void) const {
	return this->coord;
}

bool
SeaHex::hasDock(string coords) {
	unsigned int relativeCoord;
	unsigned int i;

	/* Me fijo si la coordenada es de costa */
	if (coords.find(this->coord, 0) != coords.npos) {
		/* Busco la coordenada en el arreglo */
		i = 0;
		for (string coord : externalDots) {
			relativeCoord = i % 5;
			if (matchCoords(coord, coords)) {
				/* Me fijo segun la cantidad de muelles si es valida */
				if (dockList.size() == 1)
					return (relativeCoord == 2 || relativeCoord == 3);
				else if (dockList.size() == 2)
					return (relativeCoord == 1 || relativeCoord == 0 || relativeCoord == 3 || relativeCoord == 4);
			}
			i++;
		}
	}
	return false;
}

SeaId
SeaHex::dockType(string coords) {
	unsigned int relativeCoord;
	unsigned int i;

	/* Me fijo si la coordenada es de costa */
	if (coords.find(this->coord, 0) != coords.npos) {
		/* Busco la coordenada en el arreglo */
		i = 0;
		for (string coord : externalDots) {
			relativeCoord = i % 5;
			if (matchCoords(coord, coords)) {
				/* Me fijo segun la cantidad de muelles si es valida */
				if (dockList.size() == 1) {
					return this->dockList[0];
				}				
				else if (dockList.size() == 2) {
					if (relativeCoord == 0 || relativeCoord == 1) {
						return this->dockList[0];
					}
					else {
						return this->dockList[1];
					}
				};
			}
			i++;
		}
	}

	throw exception("SeaHex - dockType se ejecuto con una coordenada invalida");
}

vector<SeaId>
SeaHex::getDocks(void) {
	return dockList;
}