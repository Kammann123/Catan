#pragma once

#include "ProtocolState.h"

#include <functional>

using namespace std;

/*
* PacketCallback - Callback para hacer peticion de un paquete
* particular para enviar o transmitir durante la comunicacion
*/
using PacketCallback = function<NetworkPacket*(void)>;

/*
* PSDataSend
* Estado de protocolo de tranmision de paquetes
* yendo a buscar el paquete particularmente a un callback
*/
class PSDataSend : public ProtocolState {
public:
	/*
	* PSDataSend
	* Se construye el estado de protocolo con un callback
	* donde se busca el paquete particular para enviar el mensaje
	* en cuestion.
	*/
	PSDataSend(NotifyCallback _notify, PacketCallback _callback);
	PSDataSend(PacketCallback _callback);

	/*
	* Rutinas de operacion del estado de protocolo
	*/
	virtual ProtocolStatus send(NetworkPacket* packet);
	virtual ProtocolStatus recv(NetworkPacket* packet);
	virtual ProtocolStatus solve(void);

private:
	PacketCallback callback;
};