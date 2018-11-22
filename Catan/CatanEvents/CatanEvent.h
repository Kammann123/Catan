#pragma once

#include "../CatanGame/Player.h"

/*
* CatanEvent
* Clase base de evento generico de Catan.
*/
class CatanEvent {
public:

	/*
	* Events
	* Tipos posibles de eventos de catan
	*/
	enum Events : unsigned int {THROW_DICES, ROBBER_CARDS, ROBBER_MOVE, BUILDING, 
		BANK_TRADE, OFFER_TRADE, PASS
	};

	/*
	* Sources
	* Fuentes posibles generadores del evento
	*/
	enum Sources : unsigned int {NETWORKING, GUI};

	/* Constructor y destructores */
	CatanEvent(Events event, Sources source, PlayerId player);
	~CatanEvent(void);

	Events getEvent(void) const;
	Sources getSource(void) const;
	PlayerId getPlayer(void) const;

private:
	Events event;
	Sources source;
	PlayerId player;
};