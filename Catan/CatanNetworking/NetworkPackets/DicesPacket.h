#pragma once

#include "NetworkPacket.h"

#include "../../CatanData/DicesData.h"

/*
* DicesPacket
* Define el paquete de datos con la informacion para determinar
* el valor de dados que tiro el otro usuario.
*/
class DicesPacket : public NetworkPacket, public DicesData {

public:
	/*
	* Constructores y destructores
	*/
	DicesPacket(unsigned int fDice, unsigned int sDice);
	DicesPacket(void);
	virtual ~DicesPacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};