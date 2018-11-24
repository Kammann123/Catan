#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/MapData.h"

/*
* MapPacket
* Paquete de datos con la informacion de la disposicion del mapa.
*/
class MapPacket : public NetworkPacket, public MapData {

public:
	/*
	* Constructores y destructores
	*/
	MapPacket(MapData data);
	MapPacket(map<unsigned char, MapValue> m);
	MapPacket(void);
	virtual ~MapPacket();
	
	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};