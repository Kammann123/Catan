#include "NetworkClient.h"

NetworkClient::
NetworkClient(void) : NetworkSocket() {

	if (good()) {

		/* Creo el resolver */
		this->resolver = new asio::ip::tcp::resolver(this->handler);

		/* Verifico ok */
		if (!this->resolver) {
			this->status = false;
			this->error = "NetworkClient - init - No se pudo abrir el resolver.";
		}
	}
}

NetworkClient::
~NetworkClient() {

	/* Limpio el resolver */
	if (this->resolver) {
		delete this->resolver;
	}
}

NetworkSocket::Types NetworkClient::
getType(void) {
	return NetworkSocket::CLIENT;
}

void NetworkClient::
connect(string ip, unsigned int port) {

	/* Verifico no conectado */
	if (!isConnected()) {

		/* Inicializo variables */
		asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string(ip), port);
		asio::error_code error;

		/* Intento realizar conexion */
		this->socket->connect(endpoint, error);

		/* Verifico errores */
		if (!handleError(error)) {
			if(error != asio::error::would_block)	toggleConnection();
		}
	}
}