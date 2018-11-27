#include "CatanNetworking/NetworkHandlers/NetworkClient.h"
#include "CatanNetworking/NetworkHandlers/NetworkServer.h"
#include "CatanNetworking/NetworkHandlers/NetworkSocket.h"

#define CONSOLE(msg) cout << "[SERVER] > " << msg << endl

int main(int argc, char** argv) {

	string ip;
	unsigned int port;

	CONSOLE("Ingrese ip: ");
	cin >> ip;
	CONSOLE("Ingrese port: ");
	cin >> port;

	NetworkClient client = NetworkClient();

	CONSOLE("Esperando conexiones...");

	while (!client.isConnected()) {
		client.connect(ip, port);
	}

	CONSOLE("Servidor conectado con exito!");

	while (client.good()) {

		client.run();

		if (client.hasReceived()) {

			NetworkPacket* packet = client.receive();
			CONSOLE("Recibido el mensaje: " + packet->getString());
		}
	}

	CONSOLE("Servidor tuvo error... saliendo!");
	getchar();
}