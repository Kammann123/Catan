#include "SeaHex.h"

const string externCoords[30] = { "A05","A0","AB0","B0","BC0","C01","C1","CG1","G1","GL1","L12","L2","LP2","P2","PS2","S23","S3","RS3","R3","RQ3","Q34","Q4","QM4","M4","MH4","H45","H5","HD5","D5","DA5" };

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

bool
SeaHex::hasDock(string coords) {
	unsigned int relativeCoord;
	unsigned int i;

	/* Me fijo si la coordenada es de costa */
	if (coords.find(this->coord, 0) != coords.npos) {
		/* Busco la coordenada en el arreglo */
		i = 0;
		for (string coord : externCoords) {
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
		for (string coord : externCoords) {
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