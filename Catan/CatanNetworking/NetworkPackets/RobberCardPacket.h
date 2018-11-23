#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/RobberCardData.h"

/*
* RobberCardPacket
* Paquete con las cartas que son descartadas ante
* la presencia del robber en una jugada!
*/
class RobberCardPacket : public NetworkPacket, public RobberCardData {
public:
	/*
	* Constructores y destructores
	*/
	RobberCardPacket(list<ResourceId> resources);
	RobberCardPacket(void);
	~RobberCardPacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};