#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/MonopolyData.h"

/*
* MonopolyPacket
* Paquete de datos para hacer uso de la carta de desarrollo monopoly!
*/
class MonopolyPacket : public NetworkPacket, public MonopolyData {
public:
	/* Constructores */
	MonopolyPacket(MonopolyData data);
	MonopolyPacket(ResourceId res);
	MonopolyPacket(void);
	~MonopolyPacket();

	/*
	* getDataStream
	* Devuelve el paquete de datos con el formato para mandarlo
	*/
	unsigned char* getDataStream(unsigned int& length);
};