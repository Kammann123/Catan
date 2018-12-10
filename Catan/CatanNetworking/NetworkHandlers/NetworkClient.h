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

	enum States : unsigned int {IDLE, CONNECTING};

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
	void reset(void);

	/*
	* connect
	* Intenta realizar una conexion del cliente, o socket, con una
	* direccion ip y puerto dados por los argumentos del metodo.
	* El metodo no es bloqueante, realiza una prueba y luego finaliza.
	*/
	void connect(string ip, unsigned int port);
	void sconnect(string ip, unsigned int port);
	void aconnect(string ip, unsigned int port);

private:

	void deadline_first(void);
	void connect_fist(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iterator);

	boost::asio::ip::tcp::resolver* resolver;
	boost::asio::deadline_timer deadline;

	string ip;
	unsigned int port;
	States state;
};