#include "NetworkServer.h"

NetworkServer::
NetworkServer(unsigned int port) : NetworkSocket() {

	if (good()) {

		/* Creo y abro el acceptor y endpoint del server */
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
		this->acceptor = new boost::asio::ip::tcp::acceptor(*this->handler, endpoint);
	
		/* Verifico ok! */
		if (this->acceptor) {
			this->port = port;
		}
		else {
			this->status = false;
			this->error = "NetworkServer - init - No pudo abrirse el acceptor";
		}
	}
}

NetworkServer::
~NetworkServer() {

	if (this->acceptor) {
		delete this->acceptor;
	}
}

NetworkSocket::Types NetworkServer::
getType(void) {
	return Types::SERVER;
}

void NetworkServer::
listen(void) {

	/* Verifico conexion */
	if (!isConnected()) {

		/* Inicializacion */
		boost::system::error_code error;
		boost::asio::ip::tcp::endpoint endpoint;

		/* Acepto nueva conexion */
		this->acceptor->accept(*socket, endpoint, error);

		/* Valido error */
		if (!handleConnection(error)) {
			toggleConnection();
			nonBlocking();
		}
	}
}