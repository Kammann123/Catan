#pragma once

#include "NetworkingState.h"
#include "../NetworkProtocols/NetworkProtocol.h"

/*
* Sync
* En este estado de CatanNetworking se ejecuta el protocolo de comunicacion para
* mandar la informacion del juego y sincronizar con el cliente que esta conectado
*/
class Sync : public NetworkingState {
public:
	/* Constructor */
	Sync(CatanNetworking& networking);
	~Sync();

	/* Acciones del estado */
	void run(void);
	void update(void);
	string what(void);
	
	/* Metodos del protocolo */
	void setRemoteName(NetworkPacket* packet);
	NetworkPacket* getLocalName(void);
	NetworkPacket* getMap(void);
	NetworkPacket* getTokens(void);
	NetworkPacket* getTurn(void);
private:
	Protocol * syncProtocol;
};