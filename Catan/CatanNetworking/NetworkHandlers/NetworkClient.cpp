#include "NetworkClient.h"

#include "boost/lambda/lambda.hpp"
#include "boost/chrono.hpp"

using boost::lambda::var;

using namespace std::placeholders;

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
		else {

			/* Estado inicial */
			state = States::IDLE;
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

		/* Almaceno la informacion del intento de conexion
		* para establecer un vinculo con los handlers hasta
		* lograr haber conectado
		*/
		this->ip = ip;
		this->port = port;

		/* Configuro el timer deadline con un tiempo determinado al cual
		* se debera ejecutar el metodo handler para comunicar un timeout
		*/
		deadline.expires_from_now(boost::posix_time::milliseconds(450));

		/* Mando al thread pool dos async tasks para que se ejecuten
		* en el io service, a cada uno le configuro su correspondiente
		* handler.
		*/
		deadline.async_wait(bind(&NetworkClient::deadline_first, this));
		
		if (state == States::IDLE) {

			/* Envio la tarea de conectarse al io_service, y paso a estado de connecting */
			boost::asio::ip::tcp::resolver::iterator endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, to_string(port)));
			boost::asio::async_connect(*socket, endpoint, bind(&NetworkClient::connect_fist, this, _1, _2));
			state = States::CONNECTING;
		}
		else if (state == States::CONNECTING) {

			/* Ejecuto o corro el handler de io_service hasta que alguna
			* tarea, una sola, se haya ejecutado, sea la conexion o le timeout
			*/
			handler->run_one();
		}
	}
}

void NetworkClient::
sconnect(string ip, unsigned int port) {

	if (!isConnected()) {
		boost::asio::ip::tcp::endpoint endpoint;
		boost::system::error_code error;

		/* Se intenta abrir el endpoint de comunicacion para
		* establecer la conexion del socket. */
		try {	
			endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port);
		}
		catch (...) {
			/* En caso de ser invalido el endpoint. Se levanta el error */
			this->status = false;
			this->error = "Informacion para conexion invalida.";
			return;
		}

		/* Intento conectar el socket */
		socket->connect(endpoint, error);
		
		/* Evaluo el estado del codigo de error de Boost Asio */
		if (!handleConnection(error)) {
			if (!error) {
				toggleConnection();
				nonBlocking();
			}
		}
	}
}

void 
NetworkClient::deadline_first(void) {
	/* Se ejecuta el handler de timeout... podria hacer algo
	* y en versiones anteriores se grababa el timeout en error_code
	* pero por el momento no tiene sentido. 
	*/
}

void 
NetworkClient::connect_fist(const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator iterator) {
	/* Verifico que tipo de error llego,
	* y en funcion de eso determino si es necesario haberse conectado
	* o mandar una nueva tarea de conexion 
	*/
	if (!handleConnection(error)) {
		if (!error) {
			toggleConnection();
			nonBlocking();
		}
		else {
			boost::asio::ip::tcp::resolver::iterator endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(ip, to_string(port)));
			boost::asio::async_connect(*socket, endpoint, bind(&NetworkClient::connect_fist, this, _1, _2));
		}
	}
}

void
NetworkClient::reset(void) {
	this->state = States::IDLE;
	this->status = false;
	this->error = "";

	if (connected) {
		this->socket->close();
		this->connected = false;
	}
}