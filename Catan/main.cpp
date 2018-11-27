#include "CatanNetworking/NetworkHandlers/NetworkClient.h"
#include "CatanNetworking/NetworkHandlers/NetworkServer.h"
#include "CatanNetworking/NetworkHandlers/NetworkSocket.h"

#define CONSOLE(msg) cout << "[SERVER] > " << msg << endl

int main(int argc, char** argv) {

	NetworkServer server = NetworkServer(13225);

	CONSOLE("Esperando conexiones...");

	while (!server.isConnected()) {
		server.listen();
	}

	CONSOLE("Servidor conectado con exito!");

	while (server.good()) {

		server.run();

		if (server.hasReceived()) {

			NetworkPacket* packet = server.receive();
			CONSOLE("Recibido el mensaje: " + packet->getString());
		}
	}

	CONSOLE("Servidor tuvo error... saliendo!");
	getchar();
}