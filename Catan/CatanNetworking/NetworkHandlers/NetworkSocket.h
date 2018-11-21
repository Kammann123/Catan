#pragma once

#include "../NetworkParsers/NetworkParser.h"

#include <asio/ip/tcp.hpp>

#include <string>
#include <deque>

using namespace std;

#define MAX_BUFFER_SIZE	1024

/*
* NetworkSocket
* Clase base de un socket para el manejo de entradas y salidas
* de mensajes de cualquier socket, actue como servidor o cliente
* ambos comparten funcionalidades propias de un NetworkSocket.
*
* Asume una conexion no bloqueante de sus implementaciones.
*/
class NetworkSocket {
public:
	
	/*
	* Types
	* Tipos de NetworkSockets como implementaciones de clase base
	*/
	enum Types : unsigned int {CLIENT, SERVER};

	/*
	* Constructores y destructores
	*/
	NetworkSocket(void);
	~NetworkSocket(void);

	/*
	* run
	* Libera los mensajes de las colas, revisando si hay bytes en el buffer de 
	* recepcion para procesar e ingresar paquetes de recvQueue, o si hay mensajes
	* en la sendQueue para emitir y enviar al otro punto de la comunicacion.
	* Actualiza las colas de paquetes de datos del socket.
	*/
	void run(void);

	/*
	* send
	* Guarda un mensaje NetworkPacket para enviar por la comunicacion
	* dentro de la cola de mensajes a enviar. Revisar otro metodo para liberar
	* los mensajes en la cola y enviarlos.
	*/
	void send(NetworkPacket* packet);

	/*
	* receive
	* Recibe y devuelve un mensaje NetworkPacket guardado en la cola de mensajes
	* recibidos y esperando ser procesados. Revisar otro metodo para poder
	* actualizar esa cosa de mensajes.
	*/
	NetworkPacket* receive(void);

	/*
	* hasReceived
	* Revisa y devuelve si hay mensajes recibidos para tomar de la cosa.
	*/
	bool hasReceived(void) const;

	/*
	* isConnected
	* Verifico si esta conectado el socket, devuelve True/False.
	*/
	bool isConnected(void) const;

	/*
	* good
	* Devuelve si el estado del socket esta bien o no, para saber si
	* hubo algun error o no durante la emision o recepcion de mensajes,
	* o conexiones de sus implementaciones.
	* A saber, los errores se piden con otro metodo.
	*/
	bool good(void) const;

	/*
	* getError
	* Devuelve un mensaje con la informacion del error en caso de haberlo.
	* Verifico si hubo o no error, previamente, con otro metodo!
	*/
	string getError(void) const;

	/*
	* clearError
	* Libera y limpia el error y estado del socket
	*/
	void clearError(void);

	/*
	* getType
	* Metodo virtual que permite saber si el NetworkSocket es un
	* cliente o server, segun la implementacion
	*/
	virtual Types getType(void) = 0;

protected:

	/*
	* toggleConnection
	* Cambia el estado de conexion, inviertiendo el estado actual
	*/
	void toggleConnection(void);

	/*
	* handleError
	* Maneja los errores recibidos durante las ejecuciones del Socket
	* cambia el estado y almacenando mensajes internos para cada caso.
	*
	* Si no hubo error devuelve false.
	*/
	bool handleError(asio::error_code error);

	/*
	* sendPacket
	* Libera un paquete de datos de la cola del socket y lo manda
	* por la comunicacion TCP
	*/
	void sendPacket(void);

	/*
	* receivePacket
	* Recibe paquetes de bytes y los manda al parser, creando paquetes
	* para la cola
	*/
	void receivePacket(void);

	NetworkParser parser;
	deque<NetworkPacket*> sendQueue;
	deque<NetworkPacket*> recvQueue;

	bool connected;
	bool status;
	string error;

	asio::io_service* handler;
	asio::ip::tcp::socket* socket;
};