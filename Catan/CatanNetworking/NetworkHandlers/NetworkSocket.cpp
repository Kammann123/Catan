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
	this->socket->non_blocking(true);
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
receive(void) {
	if (hasReceived()) {
		NetworkPacket* temp = this->recvQueue.front();
		this->recvQueue.pop_front();
		return temp;
	}
	else {
		return nullptr;
	}
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

		/* Que no sea que sea bloqueante */
		if (error != boost::asio::error::would_block) {

			this->status = false;
			this->error = error.message();
			return true;
		}
	}
	return false;
}