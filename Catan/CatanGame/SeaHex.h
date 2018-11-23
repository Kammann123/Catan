#pragma once

#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"
#include <string>

using namespace std;

const string externCoords[] = {"A05","A0","AB0","B0","BC0","C01","C1","CG1","G1","GL1","L12","L2","}
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