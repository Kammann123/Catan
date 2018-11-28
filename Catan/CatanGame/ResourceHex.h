#pragma once

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

#include "Player.h"
#include "Coord.h"

#include <string>

using namespace std;
class ResourceHex {

public:

	/*
	* Constructor
	*/
	ResourceHex();
	ResourceHex(const ResourceHex& copy);
	ResourceHex(Coord coord_);
	ResourceHex(ResourceId resource_, Coord coord_);
	ResourceHex(ResourceId resource_, unsigned int token__, Coord coord_);

	/*
	* getCoord()
	* Devuelve la coordenada del resourceHex
	*/
	Coord getCoord(void);

	/*
	* setCoord()
	* Define el valor de posicion del hex
	*/
	void setCoord(Coord coord);

	/*
	* getToken()
	* Devuelve el token del resourceHex
	*/
	unsigned int getToken(void);

	/*
	* setToken()
	* Define el token del resourceHex
	*/
	void setToken(unsigned int newToken);

	/*
	* getResource()
	* Devuelve el resource del resourceHex
	*/
	ResourceId getResource(void);
	const char* getLand(void);

	/*
	* setResource()
	* Define el resource del resourceHex
	*/
	void setResource(ResourceId newResource);

private:
	unsigned int token;
	ResourceId resource;
	Coord coord;
};