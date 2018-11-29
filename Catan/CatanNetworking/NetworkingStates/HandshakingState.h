#pragma once

#include "NetworkingState.h"
#include "../NetworkProtocols/NetworkProtocol.h"
#include "../CatanNetworking.h"

#define TIMEOUT_TIME	10

/*
* HandshakingState
* Se define este estado del networking para determinar aquellos estados en los cuales
* unicamente se define un protocolo y se ejecuta ese protoclo como corresponde.
*/
class HandshakingState : public NetworkingState {
public:
	/* Constructor */
	HandshakingState(CatanNetworking& net, unsigned int id);
	~HandshakingState();

	/*
	* setProtocol
	* Permite configurar el puntero para la ejecucion
	* del protocolo de comunicacion
	*/
	void setProtocol(Protocol* protocol);
	Protocol* getProtocol(void);

	/* 
	* isHeader
	* Devuelve si es header inicial del protocolo para dar inicio
	* a su sequencia, sirve para hacer validaciones y dispatch
	* y permite ademas comparar si es el tipo de estado que se desea
	* LISTENER, TELLER o bien BOTH
	*/
	bool isHeader(PacketHeader header);
	bool isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat);

	/*
	* confirm
	* Todos los handshaking tienen que confirmarle al juego jugadas
	* notificando que la otra punta lo recibio ok.
	*/
	void confirm(NetworkPacket* packet);
	
	/* Acciones del estado */
	virtual void run(void);
	virtual void update(void);
	virtual void context(void);
private:
	Protocol * handshakingProtocol;
};