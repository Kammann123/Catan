#pragma once

#include "NetworkingState.h"

/*
* Sync
* En este estado de CatanNetworking se ejecuta el protocolo de comunicacion para
* mandar la informacion del juego y sincronizar con el cliente que esta conectado
*/
class Sync : public NetworkingState {
public:
	/* Constructor */
	Sync(CatanNetworking& networking);

	/* Acciones del estado */
	void run(void);
	void update(void);
	string what(void);
};