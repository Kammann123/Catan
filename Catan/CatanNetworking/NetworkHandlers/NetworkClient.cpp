#include "NetworkClient.h"

NetworkClient::
NetworkClient(void) : NetworkSocket() {

	if (good()) {

		/* Creo el resolver */
		this->resolver = new boost::asio::ip::tcp::resolver(*this->handler);

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
		boost::asio::ip::tcp::resolver::iterator endpoint;
		boost::system::error_code error;

		/* Intento crear el resolver */
		try {
			endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, to_string(port)));
		}
		catch (...) {
			this->status = false;
			this->error = "NetworkClient - connect - No se pudo abrir una conexion con ese host. Invalido.";
			return;
		}

		/* Intento realizar conexion */
		boost::asio::connect(*socket, endpoint, error);

		/* Verifico errores */
		if (!handleConnection(error)) {
			toggleConnection();
			nonBlocking();
		}
	}
}