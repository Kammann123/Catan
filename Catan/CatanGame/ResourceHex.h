#pragma once

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"
#include "../CatanGui/AllegroUI/FrameUI.h"

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
	ResourceHex(ResourceId resource);
	ResourceHex(const ResourceHex& copy);

	/*
	* getters - Permiten extraer y acceder a la informacion
	*/
	Coord getCoord(void);
	const char* getLand(void);
	unsigned int getToken(void);
	ResourceId getResource(void);

	/*
	* place - Ubica en la posicion correspondiente al
	* resource hex
	*/
	void place(Coord coord);

	/*
	* setToken
	* Define el token del resourceHex
	*/
	void setToken(unsigned int newToken);

private:
	unsigned int token;
	ResourceId resource;
	Coord coord;
};