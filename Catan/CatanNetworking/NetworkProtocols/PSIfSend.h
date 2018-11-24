#pragma once

#include "ProtocolState.h"

/*
* PSIfSend
* Permite definir un estado para accionar segun cada WaitSend que se permita
* de forma condicional
*/
class PSIfSend : public ProtocolState {
public:
	/* Constructores */
	PSIfSend(map<string, ProtocolState*> states);

	/*
	* Implementacion de las rutinas de operacion del
	* estado del protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);
	virtual map<string, ProtocolState*>* getSubStates(void);

private:
	map<string, ProtocolState*> states;
};