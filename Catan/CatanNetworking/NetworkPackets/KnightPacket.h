#pragma once

#include "NetworkPacket.h"

/*
* KnightPacket
* Paquete de datos con la informacion para mandar la carta de Knight
*/
class KnightPacket : public NetworkPacket {
public:
	/* Constructores y destructores */
	KnightPacket(void);
	~KnightPacket();

	/*
	* setCoord
	* Establece la coordenada para el robber
	*/
	bool setCoord(unsigned char coord);

	/*
	* getCoord
	* Devuelve la nueva coordenada para el roober
	*/
	unsigned char getCoord(void);

	/*
	* getDataStream
	* Devuelve el paquete de datos directo para mandar
	*/
	unsigned char* getDataStream(unsigned int& length);

private:
	unsigned char coord;
};