#pragma once

#include "CatanData.h"

#include <list>

using namespace std;

#define MAX_CARDS 25

/*
* DevCardsData
* Implementacion con la informacion del mazo ordenado de cartas de desarrollo
*/
class DevCardsData : public CatanData {
public:
	/* Constructores */
	DevCardsData(list<DevCardId> cards);
	DevCardsData();

	/* Setters y getters */
	bool setCard(DevCardId card);
	list<DevCardId>& getCards(void);
private:
	list<DevCardId> cards;
};