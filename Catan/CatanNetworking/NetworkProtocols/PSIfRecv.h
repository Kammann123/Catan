#pragma once

#include "ProtocolState.h"

#include <list>
#include <map>

using namespace std;

class PSRecv;

/*
* PSIfRecv
* Estado de protocolo condicional a la espera de ejecutar alguno de los
* diferentes protocolo de recepcion con los cuales se define
*/
class PSIfRecv : public ProtocolState {
public:
	/* Constructores */
	PSIfRecv(map<string, ProtocolState*> states);

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