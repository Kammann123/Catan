#pragma once

#include "Coord.h"
#include "../CatanGui/AllegroUI/MouseUI.h"

/*
* Robber
* La mejor clase del mundo para el Robber del juego.
*/
class Robber : public MouseUI {
public:
	/* Constructor */
	Robber(Coord coord);
	Robber();

	/* 
	* getCoord
	* Devuelve la posicion actual del robber
	*/
	Coord getCoord(void) const;

	/*
	* setCoord
	* Mueve el robber de posicion
	*/
	void setCoord(Coord coord);

private:
	Coord coord;
};