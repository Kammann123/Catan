#pragma once

#include "NetworkPacket.h"

/*
* MonopolyPacket
* Paquete de datos para hacer uso de la carta de desarrollo monopoly!
*/
class MonopolyPacket : public NetworkPacket {
public:
	MonopolyPacket(void);
	~MonopolyPacket();

	/*
	* setResource
	* Establece que recurso elige tomar de los demas
	*/
	void setResource(ResourceId resource);

	/*
	* getResource
	* Devuelve el recurso escogido
	*/
	ResourceId getResource(void);

	/*
	* getDataStream
	* Devuelve el paquete de datos con el formato para mandarlo
	*/
	unsigned char* getDataStream(unsigned int& length);

private:
	ResourceId resource;
};