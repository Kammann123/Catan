#pragma once

#include "NetworkPacket.h"
#include "../../CatanData/YOPData.h"

/*
* YOPPacket
* Paquete de datos para ejecutar el uso de la carta Years Of Plenty
*/
class YOPPacket : public NetworkPacket, public YOPData {

public:

	/* Constructores y destructores */
	YOPPacket(ResourceId fRes, ResourceId sRes);
	YOPPacket(void);
	~YOPPacket();

	/*
	* getDataStream
	* Devuelve el paquete como bytes para la comunicacion
	*/
	unsigned char* getDataStream(unsigned int& length);
};