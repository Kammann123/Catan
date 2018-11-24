#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/BuildingData.h"

BuildingType buildingType(PacketHeader header);
PacketHeader buildingHeader(BuildingType type);

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
	BuildingPacket(BuildingData data);
	BuildingPacket(PacketHeader header, string coords);
	BuildingPacket(PacketHeader header);
	virtual ~BuildingPacket();

	/* 
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};