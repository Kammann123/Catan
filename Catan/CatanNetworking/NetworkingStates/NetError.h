
#pragma once

#include "NetworkingState.h"

/*
* NetError
* NetError es el estado de CatanNetworking en el cual hubo un error de
* protocolo, parseo, o durante la secuencia del juego, por lo cual,
* debe comunicar ERROR al otro extremo de la comunicacion, y quedar 
* inhabilitado el uso de CatanNetworking.
*/
class NetError : public NetworkingState {
public:
	/* Constructor */
	NetError(CatanNetworking& networking);

	/* Acciones del estado */
	void run(void);
	void update(void);
	void context(void);
};