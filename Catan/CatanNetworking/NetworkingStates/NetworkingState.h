#pragma once

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
	NetworkingState(CatanNetworking& _networking, unsigned int id);
	~NetworkingState();

	/*
	* Metodos y rutinas de ejecucion en Networking
	*
	* -run: Recibe un paquete del extremo de comunicacion
	* -update: Peticion de mandar un mensaje o paquete
	* -what: Devuelve una descripcion del estado
	*/
	virtual void run(void) = 0;
	virtual void update(void) = 0;

	unsigned int getId(void);

protected:
	CatanNetworking& networking;
	unsigned int id;
};