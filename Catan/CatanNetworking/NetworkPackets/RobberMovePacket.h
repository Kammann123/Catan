#pragma once

#include "NetworkPacket.h"

/*
* RobberMovePacket
* Paquete de datos con el movimiento del robber a una
* nueva posicion correspondiente
*/
class RobberMovePacket : public NetworkPacket {
public:
	/*
	* Constructores y destructores
	*/
	RobberMovePacket(void);
	virtual ~RobberMovePacket();

	/*
	* setCoord
	* Define la coordenada a la cual para el robber.
	* En caso de ser invalida, devuelve False.
	*/
	bool setCoord(unsigned char coord);

	/*
	* getCoord
	* Devuelve la coordenada
	*/
	unsigned char getCoord(void);

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);

private:
	unsigned char coord;
};