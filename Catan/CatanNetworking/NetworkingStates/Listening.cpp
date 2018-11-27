#include "Listening.h"

#include "../NetworkHandlers/NetworkServer.h"
#include "../CatanNetworking.h"
#include "NetError.h"
#include "Sync.h"

Listening::
Listening(CatanNetworking& networking) : NetworkingState(networking, CatanNetworking::States::LISTENING ) {}

void
Listening::context() {
	/* Abro un nuevo socket como servidor */
	unsigned int port = networking.getPort();
	NetworkSocket* socket = new NetworkServer(port);
	networking.setSocket(socket);
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
			networking.changeState(CatanNetworking::States::SYNC);
		}
	}
	else {
		/* Cambio de estado a error */
		networking.changeState(CatanNetworking::States::NET_ERROR);
	}
}

void
Listening::update() {
	networking.setError("WaitSync - Hubo un error en el protocolo de sincronizacion!");
	networking.changeState(CatanNetworking::States::NET_ERROR);
}