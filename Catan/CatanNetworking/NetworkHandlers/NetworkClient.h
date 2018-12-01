#pragma once

#include "NetworkSocket.h"

/*
* NetworkClient
* Implementacion de un NetworkSocket que establece una comunicacion como
* cliente con otro punto de comunicacion, a traves de una direccion IP y un
* puerto dado.
*/
class NetworkClient : public NetworkSocket {
public:

	/*
	* Constructores y destructores
	*/
	NetworkClient(void);
	~NetworkClient(void);

	/*
	* getType
	* Implementacion de la verificacion del tipo de socket
	*/
	Types getType(void);

	/*
	* connect
	* Intenta realizar una conexion del cliente, o socket, con una
	* direccion ip y puerto dados por los argumentos del metodo.
	* El metodo no es bloqueante, realiza una prueba y luego finaliza.
	*/
	void connect(string ip, unsigned int port);
	void connect(boost::asio::ip::tcp::resolver::iterator endpoint, boost::system::error_code* err);

private:
	boost::asio::ip::tcp::resolver* resolver;
};