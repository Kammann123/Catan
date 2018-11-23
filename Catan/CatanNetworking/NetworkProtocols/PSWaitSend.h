#pragma once

#include "ProtocolState.h"

#include <list>

using namespace std;

/*
* PSWaitSend
* Estado de protocolo de transmision de mensaje a la 
* espera de recibir la informacion apropiada.
*/
class PSWaitSend : public ProtocolState {
public:
	/*
	* PSSend
	* Se construye el estado del protocolo con el callback
	* para poder notificar y luego los header que son validos
	* para enviar en esta etapa.
	*/
	PSWaitSend(NotifyCallback notify, PacketHeader _expected);
	PSWaitSend(NotifyCallback notify, list<PacketHeader> _expected);
	PSWaitSend(list<PacketHeader> _expected);

	/*
	* Implementacion de las rutinas de operacion del
	* estado del protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);

private:
	list<PacketHeader> expected;
};