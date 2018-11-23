#pragma once

#include "../CatanData/CatanData.h"
#include <string>
#include <list>

using namespace std;

const string externCoords[30] = { "A05","A0","AB0","B0","BC0","C01","C1","CG1","G1","GL1","L12","L2","LP2","P2","PS2","S23","S3","RS3","R3","RQ3","Q34","Q4","QM4","M4","MH4","H45","H5","HD5","D5","DA5" };
/*
* SeaHex
* Porcion del mapa con mar, que representa un muelle con acceso a 
* intermacion de algun tipo.
*/
class SeaHex {
public:

	/* Constructores */
	SeaHex(unsigned char coord, SeaId dockOne, SeaId dockTwo);
	SeaHex(unsigned char coord, SeaId onlyDock);

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
	list<SeaId> dockList;

};