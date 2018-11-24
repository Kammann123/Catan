#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/DevCardsData.h"

/*
* DevCardPacket
* Contiene el paquete de datos para informar
* como es el mazo de cartas de desarrollo
*/
class DevCardPacket : public NetworkPacket, public DevCardsData {
public:

	/*
	* Constructores y desctructores
	*/
	DevCardPacket(DevCardsData data);
	DevCardPacket(list<DevCardId> cards);
	DevCardPacket(void);
	virtual ~DevCardPacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};