#include "CatanNetworking/NetworkHandlers/NetworkServer.h"
#include "CatanNetworking/NetworkHandlers/NetworkClient.h"
#include "CatanNetworking/NetworkPackets/NetworkPacket.h"
#include "CatanNetworking/NetworkProtocols/NetworkProtocol.h"

#include <functional>
#include <iostream>
#include <string>

using namespace std;
using namespace std::placeholders;

#define CONSOLE(msg) cout << "[NetworkServer] >> " << msg << endl

NetworkPacket* getName(void) {
	return new NamePacket("Lucas");
}

void nName(NetworkPacket* packet) { CONSOLE("Peticion de NAME recibida"); }
void sName(NetworkPacket* packet) { CONSOLE("Enviando respuesta de NAME_IS");  }
void nAck(NetworkPacket* packet) { CONSOLE("Recibido ACK! Perfecto."); }

int main(int argc, char** argv) {

	NetworkServer myServer(12345);

	Protocol myProtocol(
		bind(&NetworkServer::send, &myServer, _1),
		{
			RECV(nName, NAME),
			DATA_SEND(sName, getName),
			RECV(nAck, ACK)
		}
	);

	CONSOLE("Esperando conexiones al servidor. PUERTO: 12345");
	
	while (!myServer.isConnected()) {

		myServer.listen();
	}
	myServer.flush();

	CONSOLE("Conexion establecida con el cliente...");

	while (myServer.good()) {

		myServer.run();

		if (myServer.hasReceived()) {

			myProtocol.recv(myServer.receive());

			if (myProtocol.getStatus() == ProtocolStatus::PROTOCOL_ERROR) {
				throw exception("Error de protocolo!");
			}
		}
	}
}