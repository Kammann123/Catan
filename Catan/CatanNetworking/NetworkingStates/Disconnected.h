#pragma once

#include "NetworkingState.h"

#include <boost/chrono.hpp>

#define MIN_TIME	2000
#define MAX_TIME	5000

/*
* Disconnected
* Estado del Networking en el cual se intentan realizar conexiones
* al puerto y la ip dadas por el otro extremo con el cual se va a jugar.
* Tomando un tiempo aleatorio para determinar durante que intervalo se
* intentan realizar las conexiones, posteriormente, cierra la conexion,
* y pasa a otro modo, en el cual, se prueba conexion como Servidor.
*/
class Disconnected : public NetworkingState {
public:
	/* Constructor */
	Disconnected(CatanNetworking& networking);

	/* Acciones del estado */
	void run(void);
	void update(void);
	void context(void);

public:
	boost::chrono::steady_clock::duration time;
	boost::chrono::steady_clock::time_point start;
};