#pragma once

#include "../CatanData/CatanData.h"

#include "Coord.h"

#include <string>
#include <vector>

using namespace std;

/*
* SeaHex
* Porcion del mapa con mar, que representa un muelle con acceso a 
* intermacion de algun tipo.
*/	
class SeaHex {
public:

	/* Constructores */
	SeaHex(Coord coord, SeaId id);
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
	SeaId getDocks(void);

private:

	Coord coord;
	SeaId id;
};	