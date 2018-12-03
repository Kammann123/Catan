#pragma once

#include "../CatanData/CatanData.h"
#include "../CatanGui/AllegroUI/FrameUI.h"
#include "Coord.h"

#include <string>
#include <vector>

using namespace std;

/*
* SeaHex
* Porcion del mapa con mar, que representa un muelle con acceso a 
* intermacion de algun tipo.
*/	
class SeaHex : public FrameUI {
public:

	/* Constructores */
	SeaHex(void);
	SeaHex(SeaId id);
	SeaHex(const SeaHex& copy);

	/*
	* getters - Devuelven informacion y permiten leer informacion
	* del SeaHex correspondiente. Como la coordenada y el tipo
	* de docks.
	*/
	Coord getCoord(void) const;
	SeaId getDocks(void);

	/*
	* place - Ubica el SeaHex en una posicion del tablero determinada
	* se utiliza para modificarla al arbitrariamente asignar mapas
	*/
	void place(Coord coord);

	/*
	* hasDock
	* Devuelve true si el mar tiene un muelle 
	* en esa coordenada
	*/
	bool hasDock(Coord coords);

	/*
	* dockType
	* Devuelve el tipo de muelle en esas coordenadas
	* Si fuera invalido, se levanta una excepcion
	*/
	SeaId dockType(Coord coords);

private:
	Coord coord;
	SeaId seaId;
};	