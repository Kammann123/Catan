#pragma once

#include "NetworkPacket.h"

/*
* BankPacket
* Paquete de datos con informacion sobre cambio con banco.
*/
class BankPacket : public NetworkPacket {

public:

	/*
	* Constructores y destructores
	*/
	BankPacket();
	virtual ~BankPacket();

private:

};