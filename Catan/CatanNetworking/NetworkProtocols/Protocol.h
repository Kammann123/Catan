#pragma once

#include "ProtocolState.h"

#include "boost/chrono.hpp"

#include <vector>
#include <string>
#include <map>

using namespace std;

#define PROTOCOL_DONE	"DONE"

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
	* - timeout: Tiempo maximo de espera en milisegundos
	* - states: Estados del protocolo con sus tags respectivos
	*/
	Protocol(NetworkSocket** socket, string start, unsigned int timeout, map<string, ProtocolState*> states);
	Protocol(NetworkSocket** socket, string start, map<string, ProtocolState*> states);
	~Protocol();

	/*
	* getStatus
	* Devuelve actualmente si el protocolo tuvo un error, o esta funcionando
	* como fue definido.
	*/
	ProtocolStatus getStatus(void);

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

	/* getType - Devuelve el tipo de estado de protocolo del primer estado del 
	* del protocolo de comunicacion con lo cual se permite determinar el caracter
	* del mismo, sea LISTENER o TELLER, en caso de ser BOTH, se toma como ambos...
	*/
	ProtocolState::ProtocolType getType(void);

	/*
	* isHeader
	* Devuelve true si el header en particular marca el inicio de la secuencia
	* del protocolo en cuestion.
	*/
	bool isHeader(PacketHeader header);
	bool isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat);

	/*
	* reset
	* Reinicia el protocolo a su estado inicial por defecto.
	*/
	void reset(void);

	/*
	* start
	* Inicia el protocolo ejecutando el primer estado en solve
	*/
	void start(void);

private:

	/*
	* transition
	* Maneja una transicion dentro del protocolo de comunicacion
	*/
	void transition(ProtocolStatus status, NetworkPacket* packet = nullptr);

	/*
	* resetTimer
	* Reinicia el valor actual del timer al time_point actual.
	*/
	void resetTime(void);

	/*
	* verifyStatus
	* Verifica que el protocolo siga vivo, sino, no puede ejecutar nada
	* y levanto excepcion... porque no estan revisando las cosas.
	*/
	void verifyStatus(void) const;
	
	/* Rutionas de inicializacion */
	void _init_callback(NetworkSocket** socket);
	void _init_substates();

	ProtocolStatus status;
	string error;

	map<string, ProtocolState*> states;
	string currState;
	string startState;

	boost::chrono::steady_clock::duration timeout;
	boost::chrono::steady_clock::time_point startTime;
	bool hasTimeout;
};