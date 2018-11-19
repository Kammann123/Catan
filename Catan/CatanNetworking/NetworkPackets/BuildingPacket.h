#pragma once

#include "NetworkPacket.h"

#include <iostream>

using namespace std;

/*
* BuildingPacket
* Paquete de datos con informacion sobre la construccion de
* alguna entidad nueva, como seria City, Settlement o bien
* la de tipo Road.
*/
class BuildingPacket : public NetworkPacket {
public:

	/*
	* Constructores y destructores
	*/
	BuildingPacket(PacketHeader header);
	virtual ~BuildingPacket();

	/*
	* setCoords
	* Agrega una o varias coordenadas directamente
	*/
	void setCoords(unsigned char coord);
	void setCoords(string& coords);

	/*
	* getCoords
	* Devuelve las coordenadas del paquete
	*/
	string& getCoords(void);
	/* 
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);

private:
	string coords;
};