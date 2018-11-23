#include "CatanNetworking/NetworkHandlers/NetworkServer.h"
#include "CatanNetworking/NetworkHandlers/NetworkClient.h"
#include "CatanNetworking/NetworkPackets/NetworkPacket.h"

#include <iostream>
#include <string>

using namespace std;

#define CONSOLE(msg) cout << "[NetworkServer] >> " << msg << endl

int main(int argc, char** argv) {

	NetworkServer myServer(12345);

	CONSOLE("Esperando conexiones al servidor. PUERTO: 12345");
	
	while (!myServer.isConnected()) {

		myServer.listen();
	}
	myServer.flush();

	CONSOLE("Conexion establecida con el cliente...");

	while (myServer.good()) {

		myServer.run();

		if (myServer.hasReceived()) {

			CONSOLE("Mensaje recibido: ");

			cout << myServer.receive()->getString() << endl;
		}
	}
}