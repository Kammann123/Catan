#pragma once

#include "NetworkPacket.h"

#include <iostream>

using namespace std;

/*
* NamePacket
* Paquete de datos con el nombre del usuario
*/
class NamePacket : public NetworkPacket {
public:

	/*
	* Constructores y destructores
	*/
	NamePacket(void);
	virtual ~NamePacket();

	/*
	* setName
	* Configura o setea el nombre del usuario
	*/
	void setName(string& name);
	void setName(char letter);
	
	/*
	* getName 
	* Devuelve el nombre del usuario en el paquete
	*/
	string& getName(void);

private:
	string name;
};