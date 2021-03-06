#pragma once

#include "ProtocolState.h"

#include <list>

using namespace std;

/*
* PSRecv
* Estado de protocolo para esperar mensaje recibido del
* otro extremo de la comunicacion y permite definir en
* caso de poder esperar varias cosas, las opciones validas.
*/
class PSRecv : public ProtocolState {
public:

	/*
	* PSRecv
	* Se construye la espera de un mensaje con una lista
	* de los posibles mensajes validos a esperar, y tambien
	* el callback de notificacion del mensaje recibido.
	*/
	PSRecv(ProtocolTag* tag, NotifyCallback notify, list<PacketHeader> _expected);
	PSRecv(ProtocolTag* tag, NotifyCallback notify, PacketHeader _expected);
	PSRecv(ProtocolTag* tag, list<PacketHeader> _expected);
	PSRecv(ProtocolTag* tag, PacketHeader _expected);

	/*
	* Implementacion de las rutinas de operacion del
	* estado del protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);
	virtual bool isHeader(PacketHeader header);
	virtual bool isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat);

private:
	list<PacketHeader> expected;
};