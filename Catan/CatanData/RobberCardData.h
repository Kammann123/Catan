#pragma once

#include "CatanData.h"
#include "../CatanGame/ResourceCard.h"

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
	RobberCardData(list<ResourceCard*> resources);
	RobberCardData();

	/* Setters y getters */
	void setResource(ResourceId res);
	void setResource(ResourceCard* res);
	list<ResourceId>& getResources(void);
	list<ResourceCard*>& getResourceCards(void);

private:
	/*
	* La informacion de la accion puede darse de forma
	* local o remota, entonces aquello que se guarda es distinto
	*/
	list<ResourceId> resources;
	list<ResourceCard*> cards;
};