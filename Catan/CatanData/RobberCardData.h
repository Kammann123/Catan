#pragma once

#include "CatanData.h"

#include <list>

using namespace std;

/*
* RobberCardData
* Implementacion de la informacion de descarte de cartas
* durante el modo de juego del robber
*/
class RobberCardData : public CatanData {
public:
	/* Constructores */
	RobberCardData(list<ResourceId> resources);
	RobberCardData();

	/* Setters y getters */
	void setResource(ResourceId res);
	list<ResourceId>& getResources(void);

private:
	list<ResourceId> resources;
};