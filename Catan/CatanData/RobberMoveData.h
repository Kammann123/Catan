#pragma once

#include "CatanData.h"

#include "../CatanGame/Coord.h"

/*
* RobberMoveData
* Implementacion de la informacion para mover el robber
*/
class RobberMoveData : public CatanData {
public:

	/* Constructores */
	RobberMoveData(Coord c);
	RobberMoveData();

	/* Setters y getters */
	bool setCoord(Coord c);
	Coord getCoord(void);

private:
	Coord coord;
};