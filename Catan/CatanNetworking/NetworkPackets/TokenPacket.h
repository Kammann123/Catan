#pragma once

#include "NetworkPacket.h"

#include <map>

using namespace std;

/*
* TokenPacket
* Paquete de datos con los tokens aleatorios para cada celda
* del mapa del juego
*/
class TokenPacket : public NetworkPacket {
public:
	/*
	* Constructores y destructores
	*/
	TokenPacket(void);
	virtual ~TokenPacket();

	/*
	* setToken
	* Define un token dentro del paquete de datos
	* Si se pide una ubicacion invalida, devuelve False.
	*/
	bool setToken(unsigned char cell, unsigned char token);

	/*
	* getTokens
	* Devuelve el mapa de tokens
	*/
	map<unsigned char, unsigned char>& getTokens(void);

private:
	map<unsigned char, unsigned char> tokens;
};