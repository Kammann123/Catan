#pragma once

#include "NetworkingState.h"
#include "../NetworkHandlers/NetworkSocket.h"

#include <string>

using namespace std;

/*
* Networking
* Clase base para la implementacion de networking con State pattern
* definiendo los diferentes estados y protocolos que puede ejecutar el mismo
*
* ACLARACION: Esta clase generica permite definir lo basico para la implementacion de una clase
* de tipo networking, no obstante, la interfaz adecuada para su uso, depende de cada hijo e
* implementacion realizada, solo cuenta con la interfaz generica de errores y cambio de estados.
*/
class Networking {
public:

	/*
	* Networking
	* Se define o modeliza un networking con un estado inicial,
	* por donde inicia su funcionamiento.
	*/
	Networking(NetworkingState* state);
	~Networking();

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

protected:

	/*
	* verifyStatus
	* Verifica el estado actual de Networking, en caso de estar
	* en estado de error, levanta excepcion para indicar error en la
	* utilizacion de Networking.
	*/
	void verifyStatus(void) const;

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

	/* Garantizo acceso a NetworkingStates */
	friend class NetworkingState;

	NetworkingState* prevState;
	NetworkingState* currState;

	bool status;
	string error;
};