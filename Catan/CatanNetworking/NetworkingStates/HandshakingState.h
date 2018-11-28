#pragma once

#include "NetworkingState.h"
#include "../NetworkProtocols/NetworkProtocol.h"
#include "../CatanNetworking.h"

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

	/* 
	* isHeader
	* Devuelve si es header inicial del protocolo para dar inicio
	* a su sequencia, sirve para hacer validaciones y dispatch
	*/
	virtual bool isHeader(PacketHeader header) = 0;
	
	/* Acciones del estado */
	virtual void run(void);
	virtual void update(void);
	virtual void context(void);
private:
	Protocol * handshakingProtocol;
};