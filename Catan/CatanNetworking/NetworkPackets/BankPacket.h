#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/BankData.h"

/*
* BankPacket
* Paquete de datos con informacion sobre cambio con banco.
*/
class BankPacket : public NetworkPacket, public BankData {

public:

	/*
	* Constructores y destructores
	*/
	BankPacket(BankData data);
	BankPacket(list<ResourceId> given, list<ResourceId> recv);
	BankPacket();
	virtual ~BankPacket();

	/* 
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};