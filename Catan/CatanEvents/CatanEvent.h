#pragma once

#include "../CatanGame/Player.h"

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

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
	enum Events : unsigned int { THROW_DICES, ROBBER_CARDS, ROBBER_MOVE, BUILDING, BANK_TRADE, OFFER_TRADE, PASS, QUIT, ERROR_EVENT, CARD_IS, KNIGHT, MONOPOLY, YOP, SYNC, DEV_CARD, PLAY_AGAIN};

	/*
	* Sources
	* Fuentes posibles generadores del evento
	*/
	enum Sources : unsigned int {NETWORKING, GUI};

	/* Constructor y destructores */
	CatanEvent(NetworkPacket* packet);
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