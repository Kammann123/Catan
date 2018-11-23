#pragma once

#include "CatanData.h"

/*
* MonopolyData
* Implementacion de la informacion de la carta de desarrollo Monopoly
*/
class MonopolyData : public CatanData {
public:
	/* Constructores */
	MonopolyData(ResourceId res);
	MonopolyData();

	/* Setters y getters */
	void setResource(ResourceId res);
	ResourceId getResource(void);
private:
	ResourceId res;
};