#pragma once

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

#include "Player.h"

#include <string>

using namespace std;
class ResourceHex {

public:

	/*
	* Constructor
	*/
	ResourceHex(ResourceId resource_, unsigned int token_, unsigned char coord_);

	/*
	* getCoord()
	* Devuelve la coordenada del resourceHex
	*/
	unsigned char getCoord(void);

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

	/*
	* setResource()
	* Define el resource del resourceHex
	*/
	void setResource(ResourceId newResource);

private:
	unsigned int token;
	ResourceId resource;
	unsigned char coord;
};