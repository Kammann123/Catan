#pragma once

#include "CatanData.h"

/*
* RobberMoveData
* Implementacion de la informacion para mover el robber
*/
class RobberMoveData : public CatanData {
public:

	/* Constructores */
	RobberMoveData(unsigned char c);
	RobberMoveData();

	/* Setters y getters */
	bool setCoord(unsigned char c);
	unsigned char getCoord(void);

private:
	unsigned char coord;
};