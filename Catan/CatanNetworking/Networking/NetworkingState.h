#pragma once

#include "../NetworkPackets/NetworkPacket.h"

/* Declaracion del networking */
class Networking;

/*
* NetworkingState
* Estado del Networking para la utilizacion del
* patron de diseño State para poder cambiar el comportamiento
* de los metodos de Networking segun estados.
*/
class NetworkingState {
public:

	/*
	* Constructor de NetworkingState
	*/
	NetworkingState(Networking& _networking);
	virtual ~NetworkingState();

	/*
	* Metodos y rutinas de ejecucion en Networking
	*
	* -run: Recibe un paquete del extremo de comunicacion
	* -update: Peticion de mandar un mensaje o paquete
	*/
	virtual void run(void) = 0;
	virtual void update(void) = 0;

private:
	Networking& networking;
};