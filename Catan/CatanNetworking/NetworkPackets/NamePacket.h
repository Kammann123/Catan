#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/NameData.h"

/*
* NamePacket
* Paquete de datos con el nombre del usuario
*/
class NamePacket : public NetworkPacket, public NameData {
public:

	/*
	* Constructores y destructores
	*/
	NamePacket(string name);
	NamePacket(void);
	virtual ~NamePacket();
	
	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};