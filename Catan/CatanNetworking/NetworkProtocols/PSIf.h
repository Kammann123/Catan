#pragma once

#include "ProtocolState.h"

#include <map>

using namespace std;

/*
* PSIf
* Permite manejar un estado de protocolo en el cual se puede decidir
* entre diferentes opciones validas para manejar el flujo de la comunicacion
* determinando diferentes ProtocolStates como validos, ya sean Listeners o Tellers
*/
class PSIf : public ProtocolState {
public:
	/* Constructores */
	PSIf(map<string, ProtocolState*> states);

	/*
	* Implementacion de las rutinas de operacion del
	* estado del protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);
	virtual map<string, ProtocolState*>* getSubStates(void);
	virtual bool isHeader(PacketHeader header);

private:
	map<string, ProtocolState*> states;
};