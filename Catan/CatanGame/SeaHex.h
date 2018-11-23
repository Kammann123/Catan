#pragma once

#include "../CatanData/CatanData.h"
#include <string>
#include <list>

// cada dock tiene dos vértices de acceso
#define FIRST_DOCK_OFFSET 0

#define SECOND_DOCK_OFFSET 3

#define ONLY_DOCK_OFFSET 2

#define VERTEX_PER_SEA_PIECE 6

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
	* Devuelve la lista de docks disponibles en la pieza
	*/
	list<SeaId> getDockList(void) const;


	/*
	* getDockAbsCoords()
	* Devuelve las coordenadas absoultas del puerto solicitado, y si este no está retorna string "ERROR"
	*/
	string getDockAbsCoords(SeaId dockID);

	string getDockAbsCoords(unsigned char dockNumber); // agregar esta


private:

	unsigned char coord;
	/* Lista de docks, en sentido HORARIO (convención) */
	list<SeaId> dockList;
};	