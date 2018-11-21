#pragma once

#include "NetworkSocket.h"

/*
* NetworkServer
* Implementacion de NetworkSocket para crear un socket que funciona como servidor
* escuchando una conexion y permitiendo a partir de recibir tal conexion,
* transmision en ambas direcciones de mensajes.
*/
class NetworkServer : public NetworkSocket {
public:

	/*
	* Constructor y destructor
	*/
	NetworkServer(unsigned int port);
	~NetworkServer();

	/*
	* getType
	* Devuelve el tipo de NetworkSocket como servidor
	*/
	Types getType(void);

	/*
	* listen
	* Espera una conexion de algun cliente o socket y se realiza como
	* una operacion no bloqueante. Utilizar metodos del socket para verificar
	* si la conexion se establecio o no.
	*/
	void listen(void);

private:
	asio::ip::tcp::acceptor* acceptor;

	unsigned int port;
};