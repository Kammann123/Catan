#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/CardIsData.h"

/*
* CardIsPacket
* Paquete de datos para poder mandar una carta que nos roba el knight :(
*/
class CardIsPacket : public NetworkPacket, public CardIsData {
public:
	/* Constructores */
	CardIsPacket(CardIsData data);
	CardIsPacket(ResourceId resource);
	CardIsPacket();
	virtual ~CardIsPacket();

	/* Metodo getDataStream */
	unsigned char* getDataStream(unsigned int& length);
};