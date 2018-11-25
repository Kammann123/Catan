#pragma once

#include "NetworkHandlers/NetworkSocket.h"
#include "../CatanGame/CatanGame.h"
#include "../MVC/Observer.h"

#include <string>

#include "NetworkingStates/NetworkingState.h"

using namespace std;

/*
* IMPORTANTE RECORDATORIO
* Para entender el flujo de State pattern, recordar pensar que en cada estado,
* ver al estado, es en si mismo ver a CatanNetworking.
*
* A saber, existe 3 TIPOS DE ERRORES que pueden surgir unicamente en el proceso
* de Networking, ya sea un error con el Socket, con el Parser de paquetes, o bien
* en el Protocolo mismo de cada "conversacion", estos errores invalidan a Networking,
* a lo cual su flujo se restringe. Por si llega a olvidar verificar estos errores,
* la utilizacion de Networking posterior a algun error, levantara EXCEPCIONES!
*/

/*
* CatanNetworking
* Clase base para la implementacion de networking con State pattern
* definiendo los diferentes estados y protocolos que puede ejecutar el mismo
*/
class CatanNetworking : public Observer {
public:

	/*
	* CatanNetworking
	* Se construye el CatanNetworking con una referencia
	* del juego para acceder a su informacion, ademas por ser observer.
	*/
	CatanNetworking(string ip, unsigned int port, CatanGame& _game);
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

	/*
	* getState
	* Devuelve el estado actual de Networking
	*/
	NetworkingState* getState(void);

	/*
	* getError
	* Devuelve el mensaje de error de Networking, si lo hubiera.
	*/
	string getError(void);

	/*
	* good
	* Devuelve true si Networking carece de errores al momento.
	*/
	bool good(void);

	/*
	* changeState
	* Cambia el estado del Networking
	*/
	void changeState(NetworkingState* state);

	/*
	* setError
	* Configura un estado de error en el Networking
	*/
	void setError(string msg);
	void setError(const char* msg);

	/*
	* getEventPacket
	* Crea un paquete de datos a partir de un Evento del juego
	*/
	NetworkPacket* getEventPacket(CatanEvent* event);

	/* Getters paara los NetworkingStates */
	CatanGame& getGame(void);
	NetworkSocket* getSocket(void);
	string getIp(void);
	unsigned int getPort(void);
	void setSocket(NetworkSocket* socket);

private:

	/*
	* verifyStatus
	* Verifica el estado actual de Networking, en caso de estar
	* en estado de error, levanta excepcion para indicar error en la
	* utilizacion de Networking.
	*/
	void verifyStatus(void) const;

private:
	string ip;
	unsigned int port;
	NetworkingState* prevState;
	NetworkingState* currState;
	bool status;
	string error;
	NetworkSocket * socket;
	CatanGame& game;
};