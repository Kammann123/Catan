#pragma once

#include "CatanData.h"

/*
* KnightData
* Implementacion de la informacion de la carta de desarrollo Knight
*/
class KnightData : public CatanData {
public:
	/* Constructores */
	KnightData(unsigned char coord);
	KnightData();

	/* Setters y getters */
	bool setCoord(unsigned char c);
	unsigned char getCoord(void);
private:
	unsigned char coord;
};