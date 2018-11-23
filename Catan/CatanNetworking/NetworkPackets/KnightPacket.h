#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/KnightData.h"

/*
* KnightPacket
* Paquete de datos con la informacion para mandar la carta de Knight
*/
class KnightPacket : public NetworkPacket, public KnightData {
public:
	/* Constructores y destructores */
	KnightPacket(unsigned char coord);
	KnightPacket(void);
	~KnightPacket();

	/*
	* getDataStream
	* Devuelve el paquete de datos directo para mandar
	*/
	unsigned char* getDataStream(unsigned int& length);
};