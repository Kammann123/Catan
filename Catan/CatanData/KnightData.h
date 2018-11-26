#pragma once

#include "CatanData.h"

#include "../CatanGame/Coord.h"

/*
* KnightData
* Implementacion de la informacion de la carta de desarrollo Knight
*/
class KnightData : public CatanData {
public:
	/* Constructores */
	KnightData(Coord coord);
	KnightData();

	/* Setters y getters */
	bool setCoord(Coord c);
	Coord getCoord(void);
private:
	Coord coord;
};