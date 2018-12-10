#include "NetworkClient.h"

#include "boost/lambda/lambda.hpp"
#include "boost/chrono.hpp"

using boost::lambda::var;
using boost::lambda::_1;

NetworkClient::
NetworkClient(void) : NetworkSocket() , deadline(*handler) {

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
	aconnect(ip, port);
}

void NetworkClient::
aconnect(string ip, unsigned int port) {

	if (!isConnected()) {

		/*
		* Abro los elementos necesarios para poder correr
		* el async_connect de boost asio
		*/
		boost::asio::ip::tcp::resolver::iterator endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, to_string(port)));
		err = boost::asio::error::would_block;

		/*
		* Configuro el deadline y el async_connect
		*/
		deadline.expires_from_now(boost::posix_time::milliseconds(100));
		boost::asio::async_connect(*socket, endpoint, var(err) = _1);
		deadline.async_wait(bind(&NetworkClient::deadline_first, this));
		handler->run_one();

		/*
		* Hago que boost espere a terminar el deadline ejecutando en el
		* medio todos los connect posibles.
		*/

		/*
		* Termino de ejecutarse porque hubo algun tipo de error
		* o mismo porque se llego al timeout o deadline configurado
		* entonces se revisa el error para definir
		*/
		if (!handleConnection(err)) {
			if (!err) {
				toggleConnection();
				nonBlocking();
			}
		}
	}
}

void NetworkClient::
sconnect(string ip, unsigned int port) {

	if (!isConnected()) {
		boost::asio::ip::tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port);

		socket->connect(endpoint, err);

		if (!handleConnection(err)) {
			if (!err) {
				toggleConnection();
				nonBlocking();
			}
		}
	}
}

void 
NetworkClient::deadline_first(void) {
	err = boost::asio::error::timed_out;
}
