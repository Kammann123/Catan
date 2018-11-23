#pragma once

#include "NetworkPacket.h"
#include "../../CatanData/TokenData.h"

/*
* TokenPacket
* Paquete de datos con los tokens aleatorios para cada celda
* del mapa del juego
*/
class TokenPacket : public NetworkPacket, public TokenData {
public:
	/*
	* Constructores y destructores
	*/
	TokenPacket(map<unsigned char, unsigned char> tokens);
	TokenPacket(void);
	virtual ~TokenPacket();

	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);
};