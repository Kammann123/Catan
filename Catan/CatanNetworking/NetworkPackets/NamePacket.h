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
	NamePacket(NameData data);
	NamePacket(string name);
	NamePacket(void);
	virtual ~NamePacket();

	/*
	* getStrign
	* Devuelve string con mensaje formateado
	*/
	virtual string getString(void);
	
	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};