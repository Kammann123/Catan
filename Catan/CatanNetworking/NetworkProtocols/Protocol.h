#pragma once

#include "ProtocolState.h"

#include <vector>
#include <string>

using namespace std;

/*
* Protocol
* Modelizacion de un protocolo de comunicacion, donde se define
* la secuencia de handshaking que hace a una conversacion.
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
	Protocol(SendCallback sendCallback, vector<ProtocolState*> states);
	~Protocol();

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

	/*
	* verifyStatus
	* Verifica que el protocolo siga vivo, sino, no puede ejecutar nada
	* y levanto excepcion... porque no estan revisando las cosas.
	*/
	void verifyStatus(void) const;

	ProtocolStatus status;
	string error;

	vector<ProtocolState*> states;
	unsigned int currentState;
};