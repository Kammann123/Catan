#pragma once

#include "CatanEvent.h"

#include "../CatanData/NameData.h"
#include "../CatanData/MapData.h"
#include "../CatanData/TokenData.h"
#include "../CatanData/DevCardsData.h"
#include "../CatanGame/Player.h"

/*
* SyncEvent
* Evento de sincronizacion de juego, para inicializarloS
*/
class SyncEvent : public CatanEvent {
public:
	/* Constructores */
	SyncEvent(Sources source);

	/* Getters y setters */
	void setLocalName(NameData name);
	void setRemoteName(NameData name);
	void setMap(MapData map);
	void setTokens(TokenData tokens);
	void setDevCards(DevCardsData cards);
	void setDevMode(bool mode);
	void setTurn(PlayerId player);

	NameData getLocalName(void);
	NameData getRemoteName(void);
	MapData getMap(void);
	TokenData getTokens(void);
	DevCardsData getDevCards(void);
	PlayerId getTurn(void);

	bool hasDevs(void);
private:
	NameData local, remote;
	MapData map;
	TokenData tokens;
	DevCardsData devs;
	
	bool withDevs;
	PlayerId turn;
};