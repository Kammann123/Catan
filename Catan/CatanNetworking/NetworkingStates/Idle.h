#pragma once

#include "NetworkingState.h"
#include "HandshakingState.h"

#include <list>

using namespace std;

/*
* Idle
* Estado de espera del networking a recibir o mandar mensajes para iniciar
* algun intercambio de datos posible
*/
class Idle : public NetworkingState {
public:
	/* Constructores */
	Idle(CatanNetworking& _networking);
	~Idle();

	/* Acciones del estado */
	virtual void run(void);
	virtual void update(void);
	virtual void context(void);

private:
	list<HandshakingState*> handlers;
};