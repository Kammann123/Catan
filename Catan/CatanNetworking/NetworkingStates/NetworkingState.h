#pragma once

#include "boost/chrono.hpp"

#include <string>

using namespace std;

/* Declaracion del networking */
class CatanNetworking;

/*
* NetworkingState
* Estado del Networking para la utilizacion del
* patron de diseño State para poder cambiar el comportamiento
* de los metodos de Networking segun estados.
*/
class NetworkingState {
public:

	/*
	* Constructor de NetworkingState
	*/
	NetworkingState(CatanNetworking& _networking, unsigned int timeout, unsigned int id);
	NetworkingState(CatanNetworking& _networking, unsigned int id);
	~NetworkingState();

	/*
	* Metodos y rutinas de ejecucion en Networking
	*
	* -run: Recibe un paquete del extremo de comunicacion
	* -update: Peticion de mandar un mensaje o paquete
	* -context: Primera accion ejecutada al entrar al estado
	*/
	virtual void run(void) = 0;
	virtual void update(void) = 0;
	virtual void context(void) = 0;
	
	/*
	* timeoutStatus
	* Devuelve true mientras no haya ningun tipo de error
	* no obstante, si detecta que el timeout esta activado
	* y por el otro lado, se pasa del tiempo, luego
	* devuelve false.
	*/
	bool timeoutStatus(void);

	unsigned int getId(void);

protected:

	/*
	* resetTime
	* Reinicia el punto de referencia para determinar el timeout
	*/
	void resetTime(void);

	CatanNetworking& networking;
	unsigned int id;

	bool hasTimeout;
	boost::chrono::steady_clock::time_point startTime;
	boost::chrono::steady_clock::duration timeout;
};