#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/RobberMoveData.h"

/*
* RobberMovePacket
* Paquete de datos con el movimiento del robber a una
* nueva posicion correspondiente
*/
class RobberMovePacket : public NetworkPacket, public RobberMoveData {
public:
	/*
	* Constructores y destructores
	*/
	RobberMovePacket(unsigned char c);
	RobberMovePacket(void);
	virtual ~RobberMovePacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};