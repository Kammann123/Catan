#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/OfferData.h"

/*
* OfferPacket
* Paquete de datos que contiene la informacion de una oferta 
* de intercambio de cartas entre jugadores
*/
class OfferPacket : public NetworkPacket, public OfferData {
public:
	/*
	* Constructores y destructores
	*/
	OfferPacket(list<ResourceId> given, list<ResourceId> recv);
	OfferPacket(void);
	virtual ~OfferPacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};