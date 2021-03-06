#pragma once

#include "ProtocolState.h"

/*
* PSRespond
* Estado de protocolo de respuesta donde se define
* un mensaje de respuesta sin cuerpo para enviar de forma
* inmediante, llegado dicho estado durante la comunicacion.
*/
class PSSend : public ProtocolState {
public:

	/*
	* PSRespond
	* Se construye el estado de respuesta con el header
	* del mensaje que hay que armar para enviar.
	*/
	PSSend(ProtocolTag* tag, PacketHeader _header);

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
	PacketHeader header;
};