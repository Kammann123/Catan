#include "NetworkClient.h"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include <boost/asio/connect.hpp>

using boost::lambda::var;
using boost::lambda::_1;

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
		connect(endpoint, &error);

		/* Verifico errores */
		if (!handleConnection(error)) {
			toggleConnection();
			nonBlocking();
		}
	}
}

void NetworkClient::
connect(boost::asio::ip::tcp::resolver::iterator endpoint, boost::system::error_code* err) {

	/* Creo un timer para definir un plazo final 
	* ademas inicializo un estado para error code */
	boost::asio::deadline_timer deadline(*handler);
	*err = boost::asio::error::would_block;

	/* Configuro inicialmente el deadline */
	boost::posix_time::time_duration timeout = boost::posix_time::milliseconds(50);
	deadline.expires_from_now(timeout);

	/* Configuro la conexion asyncronico */
	boost::asio::async_connect(*socket, endpoint, var(*err) = _1);
	do handler->run_one(); while (*err == boost::asio::error::would_block);
}