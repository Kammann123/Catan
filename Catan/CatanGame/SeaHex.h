#pragma once

#include "../CatanData/CatanData.h"

#include "Coord.h"

#include <string>
#include <vector>

/* Puntos de acceso a los docks y offsets para la tabla de puntos externos */
#define FIRST_DOCK_OFFSET 0

#define SECOND_DOCK_OFFSET 3

#define ONLY_DOCK_OFFSET 2

#define VERTEX_PER_SEA_PIECE 6

using namespace std;

/*
* SeaHex
* Porcion del mapa con mar, que representa un muelle con acceso a 
* intermacion de algun tipo.
*
* Consideraciones:
*	+ Se toma los diferentes tipos si se construye con uno o dos puertos y se despliegan los puertos en sentido horario.
*/	
class SeaHex {
public:

	/* Constructores */
	SeaHex(Coord coord, SeaId dockOne, SeaId dockTwo);
	SeaHex(Coord coord, SeaId onlyDock);
	SeaHex(const SeaHex& copy);

	/*
	* getCoord
	* Devuelve la coordenad actual del sea hex
	*/
	Coord getCoord(void) const;

	/*
	* hasDock
	* Devuelve true si el mar tiene un muelle en esa coordenada
	*/
	bool hasDock(Coord coords);

	/*
	* dockType
	* Devuelve el tipo de muelle en esas coordenadas
	* Si fuera invalido, se levanta una excepcion
	*/
	SeaId dockType(Coord coords);

	/*
	* getDocks
	* Devuelve la lista con los docks del seaHex
	*/
	vector<SeaId> getDocks(void);

private:

	Coord coord;
	vector<SeaId> dockList;
};	