#pragma once

#include "NetworkingState.h"
#include "../NetworkProtocols/NetworkProtocol.h"
#include "../../CatanEvents/SyncEvent.h"

/*
* WaitSync
* En este estado de CatanNetworking se ejecuta el protocolo de comunicacion para
* esperar la informacion del juego.
*/
class WaitSync : public NetworkingState {
public:
	/* Constructor */
	WaitSync(CatanNetworking& networking);
	~WaitSync();
	
	/* Acciones del estado */
	void run(void);
	void update(void);
	string what(void);

	/* Metodos del protocolo */
	NetworkPacket* getLocalName(void);
	void setRemoteName(NetworkPacket* packet);
	void setMap(NetworkPacket* packet);
	void setTokens(NetworkPacket* packet);
	void setTurn(NetworkPacket* packet);

private:
	Protocol * syncProtocol;
	SyncEvent * event;
};