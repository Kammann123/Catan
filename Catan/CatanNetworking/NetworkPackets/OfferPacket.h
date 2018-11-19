#pragma once

#include "NetworkPacket.h"

#include <list>

using namespace std;

/*
* OfferPacket
* Paquete de datos que contiene la informacion de una oferta 
* de intercambio de cartas entre jugadores
*/
class OfferPacket : public NetworkPacket {
public:
	/*
	* Constructores y destructores
	*/
	OfferPacket(void);
	virtual ~OfferPacket();

	/*
	* addResources
	* Agrega al listado de recursos un recurso que se
	* pide o da en el intercambio sugerido
	*/
	void addGivenResource(ResourceId resource);
	void addReceivedResource(ResourceId resource);

	/*
	* getResources
	* Devuelve el listado de recursos que se dan o 
	* reciben en el proceso de intercambio
	*/
	list<ResourceId>& getGivenResources(void);
	list<ResourceId>& getReceivedResources(void);
private:
	list<ResourceId> givenResources;
	list<ResourceId> receivedResources;
};