#include "SeaHex.h"
#include "Coord.h"

SeaHex::
SeaHex(void) : FrameUI("", 0, 0) {}

SeaHex::
SeaHex(SeaId id) : FrameUI("", 0, 0) {
	this->seaId = id;
}

SeaHex::
SeaHex(const SeaHex& copy) : FrameUI("", 0, 0) {
	this->coord = copy.coord;
	this->seaId = copy.seaId;
}

Coord
SeaHex::getCoord(void) const {
	return this->coord;
}

SeaId
SeaHex::getDocks(void) {
	return seaId;
}

void
SeaHex::place(Coord coord) {
	this->coord = coord;
}

bool
SeaHex::hasDock(Coord coords) {
	unsigned int relativeCoord;
	unsigned int i;

	/* Me fijo si la coordenada es de costa */
	if (coords.nearCoast(this->coord)) {
		/* Busco la coordenada en el arreglo */
		i = 0;
		for (string coord : externalDots) {
			relativeCoord = i % 5;
			if (coords == coord) {
				/* Me fijo segun la cantidad de muelles si es valida */
				if (seaId == SeaId::NORMAL || seaId == SeaId::STONE || seaId == SeaId::WOOD )
					return (relativeCoord == 2 || relativeCoord == 3);
				else if (seaId == SeaId::SHEEP || seaId == SeaId::BRICK || seaId == SeaId::WHEAT )
					return (relativeCoord == 1 || relativeCoord == 0 || relativeCoord == 3 || relativeCoord == 4);
			}
			i++;
		}
	}
	return false;
}

SeaId
SeaHex::dockType(Coord coords) {
	unsigned int relativeCoord;
	unsigned int i;

	/* Me fijo si la coordenada es de costa */
	if (coords.nearCoast(this->coord)) {
		/* Busco la coordenada en el arreglo */
		i = 0;
		for (string coord : externalDots) {
			relativeCoord = i % 5;
			if (coords == coord) {
				/* Me fijo segun la cantidad de muelles si es valida */
				switch (seaId) {
					case SeaId::NORMAL:
						return SeaId::NORMAL;
						break;
					case SeaId::STONE:
						return SeaId::STONE;
						break;
					case SeaId::WOOD:
						return SeaId::WOOD;
						break;
					case SeaId::SHEEP:
						if (relativeCoord == 0 || relativeCoord == 1) {
							return SeaId::NORMAL;
						}
						else {
							return SeaId::SHEEP;
						}
						break;
					case SeaId::BRICK:
						if (relativeCoord == 0 || relativeCoord == 1) {
							return SeaId::NORMAL;
						}
						else {
							return SeaId::BRICK;
						}
						break;
					case SeaId::WHEAT:
						if (relativeCoord == 0 || relativeCoord == 1) {
							return SeaId::NORMAL;
						}
						else {
							return SeaId::WHEAT;
						}
						break;
				}
			}
			i++;
		}
	}

	throw exception("SeaHex - dockType se ejecuto con una coordenada invalida");
}