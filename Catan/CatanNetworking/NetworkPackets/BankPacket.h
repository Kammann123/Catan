#pragma once

#include "NetworkPacket.h"

#include <list>

using namespace std;

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

	/*
	* addResources
	* Se agregan recursos dados o recibidos en la transaccion
	* con el banco, construyendo el paquete a medida que se 
	* recibe.
	*/
	void addGivenResources(ResourceId resource);
	void addReceivedResources(ResourceId resource);

	/*
	* getResources
	* Devuelve los recursos del paquete
	*/
	list<ResourceId>& getGivenResources(void);
	list<ResourceId>& getReceivedResources(void);

private:
	list<ResourceId> givenResources;
	list<ResourceId> receivedResources;
};