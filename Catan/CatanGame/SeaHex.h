#pragma once

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

/*
* SeaHex
* Porcion del mapa con mar, que representa un muelle con acceso a 
* intermacion de algun tipo.
*/
class SeaHex {
public:

	/* Constructores */
	SeaHex(unsigned char coord, SeaId id);

	/*
	* getCoord
	* Devuelve la coordenad actual del sea hex
	*/
	unsigned char getCoord(void) const;

	/*
	* getType
	* Devuelve el tipo de muelle del mar que tiene
	*/
	SeaId getType(void) const;

private:
	unsigned char coord;
	SeaId id;
};