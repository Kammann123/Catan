#pragma once

#include "../NetworkPackets/NetworkPacket.h"

#include "BankParser.h"
#include "BuildingParser.h"
#include "DevCardParser.h"
#include "DicesParser.h"
#include "MapParser.h"
#include "NameParser.h"
#include "OfferParser.h"
#include "RobberCardParser.h"
#include "RobberMoveParser.h"
#include "TokenParser.h"
#include "KnightParser.h"
#include "YOPParser.h"
#include "MonopolyParser.h"

#include <deque>
#include <iostream>

using namespace std;

/*
* NetworkParser
* Interpreta secuencias de bytes creando una cola con los paquetes de 
* datos que va interpretando y parseando a medida que sigue recibiendo
* mas bytes.
*/
class NetworkParser {
public:
	/* Estados del NetworkParser */
	enum Status : unsigned int {OK, ERROR};


	/* Constructores y destructores */
	NetworkParser(void);
	~NetworkParser();

	/*
	* parse
	* Dado un byte, secuencia de bytes, se interpretan y parsean, creando paquetes de datos
	* en la cola del NetworkParser.
	*/
	void parse(unsigned char byte);
	void parse(unsigned char* bytes, unsigned int length);
	void parse(string bytes);

	/*
	* getStatus
	* Devuelve el estado actual del NetworkParser.
	* En caso de devolver ERROR, revisar con getError.
	*/
	Status getStatus(void) const;

	/*
	* getError
	* Devuelve el ultimo error actualizado del NetworkParser.
	*/
	string getError(void) const;

	/*
	* getNextPacket
	* Devuelve el siguiente paquete de datos almacenado en la cola.
	*/
	NetworkPacket* getNextPacket(void);

	/*
	* hasPackets
	* Devuelve si hay paquetes de datos parseados en la cola del NetworkParser.
	*/
	bool hasPackets(void) const;

	/*
	* cleanError
	* Limpia estado de error
	*/
	void cleanError(void);

private:
	NameParser nameParser;
	BuildingParser buildingParser;
	BankParser bankParser;
	DevCardParser devCardParser;
	DicesParser dicesParser;
	MapParser mapParser;
	OfferParser offerParser;
	RobberCardParser robberCardParser;
	RobberMoveParser robberMoveParser;
	TokenParser tokenParser;
	MonopolyParser monopolyParser;
	YOPParser yopParser;
	KnightParser knightParser;

	ParserFsm* fsmActive;
	deque<NetworkPacket*> packets;
	Status status;
	string error;
};