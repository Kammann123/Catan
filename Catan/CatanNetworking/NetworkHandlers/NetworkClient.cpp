#include "NetworkClient.h"

#include "boost/lambda/lambda.hpp"

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

	if (!isConnected()) {

		/*
		* Abro los elementos necesarios para poder correr
		* el async_connect de boost asio
		*/
		boost::asio::ip::tcp::resolver::iterator endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, to_string(port)));

		boost::asio::deadline_timer deadline_(*handler);

		boost::system::error_code error = boost::asio::error::would_block;

		/*
		* Configuro el deadline y el async_connect
		*/
		deadline_.expires_from_now(boost::posix_time::milliseconds(50));
		boost::asio::async_connect(*socket, endpoint, var(error) = _1);

		/* Ejecuto el io service routine para poder ciclar el
		* connect asincronico, hasta que detecte el timer que
		* hubo un error */
		handler->run_one();

		/*
		* Termino de ejecutarse porque hubo algun tipo de error
		* o mismo porque se llego al timeout o deadline configurado
		* entonces se revisa el error para definir
		*/
		if (!handleConnection(error)) {
			if (!error) {
				toggleConnection();
				nonBlocking();
			}
		}
	}
}

void NetworkClient::
sconnect(string ip, unsigned int port) {

	if (!isConnected()) {

		boost::system::error_code error;
		boost::asio::ip::tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port);
		
		socket->connect(endpoint, error);

		if (!handleConnection(error)) {
			if (!error) {
				toggleConnection();
				nonBlocking();
			}
		}
	}
}