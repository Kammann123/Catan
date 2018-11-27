#include "CatanNetworking/NetworkHandlers/NetworkServer.h"
#include "CatanNetworking/NetworkHandlers/NetworkClient.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define CONSOLE(msg) cout << "[SOCKET] " << msg << endl

void clientTester(void);
void serverTester(void);

int main(int argc, char** argv) {

	CONSOLE("Cliente o Server? Y/N: ");
	unsigned char answer;
	cin >> answer;

	if (answer == 'Y')	clientTester();
	else if (answer == 'N') serverTester();
}

void clientTester(void) {
	
	string ip;
	unsigned int port;

	CONSOLE("Ingrese ip: ");
	cin >> ip;
	CONSOLE("Ingrese port: ");
	cin >> port;
	
	CONSOLE("Creando y abriendo el cliente.");
	NetworkClient client = NetworkClient();

	while (!client.isConnected()) {
		client.connect(ip, port);
	}

	CONSOLE("Cliente conectado con exito!");

	while (client.good()) {

		client.run();

		if (client.hasReceived()) {

			NetworkPacket* packet = client.receive();
			unsigned int length;
			unsigned char* buff = packet->getDataStream(length);
			string msg = "Recibido el mensaje: " + string((char*)buff);
			CONSOLE(msg);
		}
	}

	CONSOLE("Cliente tuvo error... saliendo!");
	getchar();
}

void serverTester(void){

	NetworkServer server = NetworkServer(13225);

	CONSOLE("Esperando conexiones...");

	while (!server.isConnected()) {
		server.listen();
	}
	server.flush();

	CONSOLE("Servidor conectado con exito!");

	while (server.good()) {

		server.run();

		if (server.hasReceived()) {

			NetworkPacket* packet = server.receive();
			unsigned int length;
			unsigned char* buff = packet->getDataStream(length);
			string msg = "Recibido el mensaje: " + string((char*)buff);
			CONSOLE(msg);
		}
	}

	CONSOLE("Servidor tuvo error... saliendo!");
	getchar();
}