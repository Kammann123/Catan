#pragma once

#include "NetworkPacket.h"

/*
* YOPPacket
* Paquete de datos para ejecutar el uso de la carta Years Of Plenty
*/
class YOPPacket : public NetworkPacket {

public:
	/* Indices de las cartas de recurso en el paquete */
	enum ResourceIndex : unsigned char {FIRST, SECOND};

	/* Constructores y destructores */
	YOPPacket(void);
	~YOPPacket();

	/*
	* Setters y getters de las cartas
	*/
	bool setFirstResource(ResourceId resource);
	bool setSecondResource(ResourceId resource);
	ResourceId getFirstResource(void);
	ResourceId getSecondResource(void);

	/*
	* getDataStream
	* Devuelve el paquete como bytes para la comunicacion
	*/
	unsigned char* getDataStream(unsigned int& length);

private:
	
	bool _set_resource(ResourceIndex index, ResourceId resource);
	
	ResourceId resources[2];
};