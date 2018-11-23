#include "../Catan/CatanNetworking/NetworkHandlers/NetworkClient.h"

#include <iostream>
#include <string>

using namespace std;

#define CONSOLE(msg) cout << "[NetworkClient] >> " << msg << endl
#define CLIENT_SEND(msg, data) CONSOLE(msg), getchar(), client.send(new NetworkPacket(data)), client.run()

int main(int argc, char** argv) {

	NetworkClient client;

	CONSOLE("Esperando autorizacion para conectar a servidor!");
	CONSOLE("Presione alguna tecla...");
	getchar();

	CONSOLE("Conectando... a localhost!");

	while (!client.isConnected()) {
		client.connect("127.0.0.1", 12345);
	}

	CONSOLE("Cliente conectado correctamente al servidor!");

	CLIENT_SEND("Enviando paquete NAME", NAME);
	CLIENT_SEND("Enviando paquete ACK", ACK);
	CLIENT_SEND("Enviando paquete DEV_CARD", DEV_CARD);
	CLIENT_SEND("Enviando paquete ROAD_BUILDING", ROAD_BUILDING);
	CLIENT_SEND("Enviando paquete I_START", I_START);

	CONSOLE("Enviando paquete NAME_IS");
	client.send(new NamePacket("Lucas"));
	client.run();

	CONSOLE("Saliendo...");
	getchar();
}