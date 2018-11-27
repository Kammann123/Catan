#include "Disconnected.h"

#include "../NetworkHandlers/NetworkClient.h"
#include "../CatanNetworking.h"

#include "NetError.h"
#include "Listening.h"
#include "WaitSync.h"

#include <iostream>

Disconnected::
Disconnected(CatanNetworking& networking) : NetworkingState(networking, CatanNetworking::States::DISCONNECTED) {}

void
Disconnected::context() {
	/* Calculo cantidad aleatoria de milisegundos */
	unsigned int delay = rand() % (MAX_TIME - MIN_TIME) + MIN_TIME;
	time = boost::chrono::milliseconds(delay);
	start = boost::chrono::steady_clock::now();

	/* Creo el socket como cliente */
	NetworkSocket* socket = new NetworkClient();
	networking.setSocket(socket);
}

void
Disconnected::run() {

	/* Intento realizar conexion */
	unsigned int port = networking.getPort();
	string ip = networking.getIp();
	NetworkClient* client = (NetworkClient*)networking.getSocket();
	client->connect(ip, port);

	/* Verifico errores del cliente */
	if (client->good()) {
		/* Verifico si esta conectado */
		if (client->isConnected()) {
			/* Cambio de estado, ya conecte como cliente */
			networking.changeState(CatanNetworking::States::WAIT_SYNC);
		}
		else {

			/* Verifico si paso el tiempo */
			if ((boost::chrono::steady_clock::now() - start) > time) {
				/* Cambio de estado, dejo de intentar como cliente */
				delete networking.getSocket();
				networking.changeState(CatanNetworking::States::LISTENING);
			}
		}
	}
	else {
		/* Cambio a estado de error */
		networking.changeState(CatanNetworking::States::NET_ERROR);
	}
}

void
Disconnected::update() {
	networking.setError("WaitSync - Hubo un error en el protocolo de sincronizacion!");
	networking.changeState(CatanNetworking::States::NET_ERROR);
}