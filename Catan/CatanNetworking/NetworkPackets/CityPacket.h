#pragma once

#include "NetworkPacket.h"

/*
* CityPacket
* Paquete de datos que contiene la informacion
* sobre la construccion de una ciudad.
*/
class CityPacket : public NetworkPacket {

public:
	
	/*
	* Constructores y destructores
	*/
	CityPacket(void);
	virtual ~CityPacket();

	/*
	* setCoord
	* Configura una coordenada para el establecimiento
	* de la nueva ciudad.
	* Si intenta usar un indice invalido, devuelve False.
	* En exito, devuelve True.
	*/
	bool setCoord(unsigned char coord, unsigned char indexCoord);

	/*
	* getCoord
	* Devuelve la coordenada pedida, en caso de pedir una coordenada no valida,
	* devuelve 0xFF
	*/
	unsigned char getCoord(unsigned char indexCoord);

private:
	unsigned char coord[3];
};