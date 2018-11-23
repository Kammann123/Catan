#pragma once

#include "Networking/Networking.h"
#include "NetworkHandlers/NetworkSocket.h"
#include "../CatanGame/CatanGame.h"
#include "../MVC/Observer.h"

/*
* CatanNetworking
* Implementacion de Networking para el juego Catan, con sus estados
* definidos como las etapas y protocolos necesarios segun lo documentado
*/
class CatanNetworking : public Networking, public Observer {
public:

	/*
	* CatanNetworking
	* Se construye el CatanNetworking con una referencia
	* del juego para acceder a su informacion, ademas por ser observer.
	*/
	CatanNetworking(CatanGame& _game);
	~CatanNetworking();

	/*
	* run 
	* Actualiza estado del socket y revisa mensajes,
	* ejecutando el protocolo y estado networking actual
	*/
	void run(void);

	/*
	* update
	* Es notificado de una actualizacion de el CatanGame
	* con lo cual busca eventos y ejecuta el protocolo o
	* estado actual networking para ello.
	*/
	void update(void);

private:

	/*
	* getEventPacket
	* Crea un paquete de datos a partir de un Evento del juego
	*/
	NetworkPacket* getEventPacket(CatanEvent* event);

	NetworkSocket * socket;
	CatanGame& game;
};