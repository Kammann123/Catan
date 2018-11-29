#include "NetworkSocket.h"

NetworkSocket::
NetworkSocket() {

	/* Abro el socket y el service */
	this->handler = new boost::asio::io_service();
	this->socket = new boost::asio::ip::tcp::socket(*this->handler);

	/* Verifico correcta apertura! */
	if (this->handler || this->socket) {
		this->status = true;
		this->error = "";
	}
	else {
		this->status = false;
		this->error = "NetworkSocket - init - No pudo abrirse socket/service.";
	}

	/* Inicializo */
	this->connected = false;
	this->sendQueue.clear();
	this->recvQueue.clear();
}

NetworkSocket::
~NetworkSocket() {

	/* Libero servicios */
	if (this->handler) {
		delete this->handler;
	}
	/* Libero el socket */
	if (this->socket) {
		delete this->socket;
	}
	/* Libero mensajes recibidos */
	for (NetworkPacket* packet : sendQueue) {
		delete packet;
	}
	/* Libero mensajes a enviar */
	for (NetworkPacket* packet : recvQueue) {
		delete packet;
	}
}

void NetworkSocket::
run(void) {

	/* Recibo algun mensaje */
	this->receivePacket();

	/* Envio algun mensaje */
	this->sendPacket();
}

void NetworkSocket::
send(NetworkPacket* packet) {
	if (packet) {
		this->sendQueue.push_back(packet);
	}
}

NetworkPacket* NetworkSocket::
look(void) {
	if (hasReceived()) {
		NetworkPacket* temp = this->recvQueue.front();
		return temp;
	}
	else {
		return nullptr;
	}
}

NetworkPacket* NetworkSocket::
receive(void) {
	NetworkPacket* temp = look();

	if (temp) {
		this->recvQueue.pop_front();
	}

	return temp;
}

bool NetworkSocket::
hasReceived(void) const {
	return !(this->recvQueue.empty());
}

bool NetworkSocket::
good(void) const {
	return this->status;
}

string NetworkSocket::
getError(void) const {
	return this->error;
}

void NetworkSocket::
clearError(void) {
	this->status = true;
	this->error = "";
}

bool NetworkSocket::
isConnected(void) const {
	return this->connected;
}

void NetworkSocket::
toggleConnection(void) {
	this->connected = this->connected ? false : true;
}

void
NetworkSocket::flush(void) {

	if (isConnected()) {
		/* Inicializo */
		boost::system::error_code error;
		unsigned char buff[MAX_BUFFER_SIZE];
		size_t count, available;

		/* Busco cantidad disponible */
		available = this->socket->available();

		/* Recibo todo */
		do {
			count = this->socket->read_some(boost::asio::buffer(buff, MAX_BUFFER_SIZE), error);
		} while (count < available && error == boost::asio::error::would_block);

		/* Handle error */
		handleError(error);
	}
}

void NetworkSocket::
sendPacket(void) {

	/* Verifico que este conectado */
	if (isConnected()) {
		/* Verifico que haya mensajes para enviar */
		if (!this->sendQueue.empty()) {

			/* Busco el siguiente mensaje a enviar */
			NetworkPacket* packet = this->sendQueue.front();

			/* Inicializo variables de transmision */
			boost::system::error_code error;
			size_t count;
			unsigned int length;
			unsigned char* data = packet->getDataStream(length);

			/* Espero a que se mande todo el paquete de datos */
			do {
				count = this->socket->write_some(boost::asio::buffer(data, length), error);

			} while (count < length && error == boost::asio::error::would_block);

			/* Libero el data stream */
			delete[] data;

			/* Realizo el handle de error */
			if (!handleError(error)) {
				this->sendQueue.pop_front();
			}
		}
	}
}

void NetworkSocket::
receivePacket(void) {

	/* Verifico conexion */
	if (isConnected()) {

		/* Inicializo las variables */
		boost::system::error_code error;
		size_t count;
		unsigned int length = (unsigned int)this->socket->available();
		unsigned char buff[MAX_BUFFER_SIZE];

		/* Busco bytes recibidos */
		do {
			count = this->socket->read_some(boost::asio::buffer(buff, MAX_BUFFER_SIZE), error);
		} while (count < length && error == boost::asio::error::would_block);

		/* Verifico estado de error */
		if (!handleError(error)) {
			/* Parseo los bytes recibidos */
			this->parser.parse(buff, (unsigned int)count);

			/* Verifico estado */
			if (this->parser.getStatus() == NetworkParser::Status::OK) {
				/* Me fijo si hay paquetes parseados ya */
				if (this->parser.hasPackets()) {
					NetworkPacket* packet = this->parser.getNextPacket();
					this->recvQueue.push_back(packet);
				}
			}
			else {
				this->status = false;
				this->error = this->parser.getError();
			}
		}
	}
}

bool NetworkSocket::
handleError(boost::system::error_code error) {

	/* Si hay algun error */
	if (error) {
		switch (error.value()) {
			/* Ante los siguientes errores, durante la emision o
			* transmision de mensajes con el socket, se detecta una
			* falla en la conexion, con lo cual, se aborta tal conexion
			* y actualiza estado en funcion de ello
			*/
			case boost::asio::error::not_connected:
			case boost::asio::error::broken_pipe:
			case boost::asio::error::eof:
			case boost::asio::error::timed_out:
			case boost::asio::error::host_not_found:
			case boost::asio::error::host_not_found_try_again:
			case boost::asio::error::host_unreachable:
			case boost::asio::error::network_unreachable:
			case boost::asio::error::network_down:
			case boost::asio::error::network_reset:
			case boost::asio::error::connection_aborted:
			case boost::asio::error::connection_refused:
			case boost::asio::error::connection_reset:
				this->connected = false;
				this->status = false;
				this->error = error.message();
				return true;
				break;

			/* Si el error es would_block, entonces no hay problemas
			* ya que esta habilitado como no bloqueante
			*/
			case boost::asio::error::would_block:
				return false;
				break;
		}
	}

	/*
	* Para todos los errores que no defino, cuyo caso no me interesa
	*/
	return false;
}

bool NetworkSocket::
handleConnection(boost::system::error_code error) {

	/* Verifico que exista error */
	if (error) {
		switch (error.value()) {

			/* Se definen todos aquellos codigos de error
			* en los cuales asio define un estado que me interesa no tomar como
			* error ya que debo seguir intentando la conexion
			*/
			case boost::asio::error::connection_refused:
			case boost::asio::error::already_connected:
			case boost::asio::error::host_not_found:
			case boost::asio::error::host_not_found_try_again:
			case boost::asio::error::host_unreachable:
			case boost::asio::error::in_progress:
			case boost::asio::error::network_unreachable:
			case boost::asio::error::not_connected:
			case boost::asio::error::not_found:
			case boost::asio::error::would_block:
				return true;

			/*
			* En los que casos que me interesa que sea un error
			* guardo un estado de error en el cliente con su mensaje respectivo
			*/
			default:
				this->status = false;
				this->error = error.message();
				return true;
		}
	}
	else {
		return false;
	}
}

void NetworkSocket::
nonBlocking(void) {
	this->socket->non_blocking(true);
}