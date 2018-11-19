#pragma once

#include "NetworkPacket.h"

#include <list>

using namespace std;

/*
* RobberCardPacket
* Paquete con las cartas que son descartadas ante
* la presencia del robber en una jugada!
*/
class RobberCardPacket : public NetworkPacket {
public:
	/*
	* Constructores y destructores
	*/
	RobberCardPacket(void);
	~RobberCardPacket();

	/*
	* addResource
	* Agrega un recurso a la lista de los descartados
	*/
	void addResource(ResourceId resource);

	/*
	* getResources
	* Devuelve los recursos que estan siendo descartados
	*/
	list<ResourceId>& getResources(void);
private:
	list<ResourceId> resources;
};