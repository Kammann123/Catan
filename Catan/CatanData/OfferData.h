#pragma once

#include "CatanData.h"

#include <list>

using namespace std;

/*
* OfferData
* Implementacion de informacion de una transaccion u oferta de intercambio de cartas
*/
class OfferData : public CatanData {
public:
	/* Constructores */
	OfferData(list<ResourceId> given, list<ResourceId> recv);
	OfferData();

	/* Setters y getters */
	void setGiven(ResourceId res);
	void setRecv(ResourceId res);
	list<ResourceId>& getGiven(void);
	list<ResourceId>& getRecv(void);
private:
	list<ResourceId> given;
	list<ResourceId> recv;
};