#include "NetworkServer.h"

NetworkServer::
NetworkServer(unsigned int port) : NetworkSocket() {

	if (good()) {

		/* Creo y abro el acceptor y endpoint del server */
		asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
		this->acceptor = new asio::ip::tcp::acceptor(*this->handler, endpoint);
	
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
		asio::error_code error;
		asio::ip::tcp::endpoint endpoint;

		/* Acepto nueva conexion */
		this->acceptor->accept(*socket, endpoint, error);

		/* Valido error */
		if (!handleError(error)) {
			if (error != asio::error::would_block)	toggleConnection();
		}
	}
}