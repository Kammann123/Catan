#include "Listening.h"

#include "../NetworkHandlers/NetworkServer.h"
#include "../CatanNetworking.h"
#include "NetError.h"
#include "Sync.h"

Listening::
Listening(CatanNetworking& networking) : NetworkingState(networking, NETWORKING_TIMEOUT, CatanNetworking::States::LISTENING ) {}

void
Listening::context() {
	/* Abro un nuevo socket como servidor */
	unsigned int port = networking.getPort();
	NetworkSocket* socket = new NetworkServer(port);
	networking.setSocket(socket);

	/* Mensaje informativo */
	networking.setInfo("[Networking] - Listening -> Abriendo servidor. Esperando conexiones...");
}

void
Listening::run() {

	/* Escucho nuevas conexiones */
	NetworkServer* server = (NetworkServer*)networking.getSocket();
	server->listen();

	/* Verifico si hubo algun error */
	if (server->good()) {

		/* Verifico si recibio conexiones */
		if (server->isConnected()) {
			/* Comunico a CatanGame evento de sincronizacion */
			networking.getGame().handle(new CatanEvent(CatanEvent::Events::ASK_SYNC, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO));
			/* Cambio de estado a sincronizacion */
			networking.changeState(CatanNetworking::States::SYNC, "[Networking] - Listening -> Conexion establecida! Comenzando sincronizacion.");
		}
	}
	else {
		/* Cambio de estado a error */
		networking.setError("[Networking] - Listening -> Hubo un error en la conexion TCP del servidor.");
		networking.changeState(CatanNetworking::States::NET_ERROR);
	}
}

void
Listening::update() {
	networking.setError("[Networking] - Listening -> Llamada inesperada de la rutina update.");
	networking.changeState(CatanNetworking::States::NET_ERROR);
}