#include "../Catan/CatanNetworking/NetworkHandlers/NetworkClient.h"
#include "../Catan/CatanNetworking/NetworkProtocols/NetworkProtocol.h"

#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;

#define CONSOLE(msg) cout << "[NetworkClient] >> " << msg << endl
#define CLIENT_SEND(msg, data) CONSOLE(msg), getchar(), client.send(new Networ

void gName(NetworkPacket* packet) { 
	CONSOLE("Recibiendo paquete NAME_IS");
	cout << "Se llama: " << ((NamePacket*)packet)->getName() << endl;
}

int main(int argc, char** argv) {

	NetworkClient client;
	Protocol myProtocol(
		bind(&NetworkClient::send, &client, _1),
		{
			SEND(NAME),
			RECV(gName, NAME_IS),
			SEND(ACK)
		}
	);

	CONSOLE("Esperando autorizacion para conectar a servidor!");
	CONSOLE("Presione alguna tecla...");
	getchar();

	CONSOLE("Conectando... a localhost!");

	while (!client.isConnected()) {
		client.connect("127.0.0.1", 12345);
	}

	CONSOLE("Cliente conectado correctamente al servidor!");

	while (client.isConnected()) {

		client.run();

		if (client.hasReceived()) {

			if (myProtocol.getStatus() != ProtocolStatus::DONE) {

				myProtocol.recv(client.receive());

				if (myProtocol.getStatus() == ProtocolStatus::PROTOCOL_ERROR) {
					throw exception("Error en el protocolo!");
				}
			}
		}
	}

	CONSOLE("Saliendo...");
	getchar();
}