#pragma once

#include "ProtocolState.h"

#include <vector>
#include <string>

using namespace std;

/*
* SendCallback - Transmision de mensajes a traves del handler
* correspondiente.
*/
using SendCallback = function<void(NetworkPacket*)>;

/*
* Protocol
* Modelizacion de un protocolo de comunicacion, donde se define
* la secuencia de handshaking que hace a una conversacion.
*
*/
class Protocol {
public:

	/*
	* Protocol
	* Definicion de un protocolo de comunicacion, o conversacion
	* entre pares para resolver alguna tarea.
	* Requiere definirse:
	* - sendCallback: Callback de transmision de paquete
	* - states: Estados del protocolo
	*/
	Protocol(SendCallback sendCallback, vector<ProtocolState> states);

	/*
	* getStatus
	* Devuelve actualmente si el protocolo tuvo un error, o esta funcionando
	* como fue definido.
	*/
	ProtocolStatus getStatus(void) const;

	/*
	* getError
	* Devuelve el mensaje de error del protocolo
	*/
	string getError(void) const;

	/*
	* Rutinas de operacion del protocolo, para comunicarle al mismo
	* la necesidad de enviar o recibir un mensaje, verificando posteriormente
	* con el Status del mismo, si cumplio con el protocolo o no.
	*/
	void send(NetworkPacket* packet);
	void recv(NetworkPacket* packet);

	/*
	* reset
	* Reinicia el protocolo a su estado inicial por defecto.
	*/
	void reset(void);

private:

	/*
	* transition
	* Maneja una transicion dentro del protocolo de comunicacion
	*/
	void transition(ProtocolStatus status);
	void transition(ProtocolStatus status, NetworkPacket* packet);

	SendCallback sendCallback;
	ProtocolStatus status;
	string error;

	vector<ProtocolState> states;
	unsigned int currentState;
};