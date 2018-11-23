#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/BuildingData.h"

/*
* BuildingPacket
* Paquete de datos con informacion sobre la construccion de
* alguna entidad nueva, como seria City, Settlement o bien
* la de tipo Road.
*/
class BuildingPacket : public NetworkPacket, public BuildingData {
public:

	/*
	* Constructores y destructores
	*/
	BuildingPacket(PacketHeader header, string coords);
	BuildingPacket(PacketHeader header);
	virtual ~BuildingPacket();

	/* 
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};