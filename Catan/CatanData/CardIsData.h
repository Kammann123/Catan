#pragma once

#include "CatanData.h"

/*
* CardIsData
* Implementacion de la respuesta a dar una carta ante el robo de un Knight
*/
class CardIsData : public CatanData {
public:
	/* Constructores */
	CardIsData(ResourceId res);
	CardIsData();

	/* Setters y getters */
	void setResource(ResourceId res);
	ResourceId getResource(void);
private:
	ResourceId resource;
};