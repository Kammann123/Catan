#pragma once

#include "NetworkingState.h"

/*
* Listening
* En este estado el Networking se queda a la espera de una conexion
* escuchando el puerto correspondiente continuamente como server
* hasta que reciba tal conexion, caso contrario, queda en espera.
*/
class Listening : public NetworkingState {
public:
	/* Constructor */
	Listening(CatanNetworking& networking);

	/* Acciones del estado */
	void run(void);
	void update(void);
	void context(void);
};