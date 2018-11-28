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
	PSWaitSend(ProtocolTag* tag, NotifyCallback notify, PacketHeader _expected);
	PSWaitSend(ProtocolTag* tag, NotifyCallback notify, list<PacketHeader> _expected);
	PSWaitSend(ProtocolTag* tag, list<PacketHeader> _expected);
	PSWaitSend(ProtocolTag* tag, PacketHeader _expected);

	/*
	* Implementacion de las rutinas de operacion del
	* estado del protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);
	virtual bool isHeader(PacketHeader header);

private:
	list<PacketHeader> expected;
};