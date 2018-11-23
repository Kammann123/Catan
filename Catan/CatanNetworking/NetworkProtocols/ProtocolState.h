#pragma once

#include "../NetworkPackets/NetworkPacket.h"
#include "../../CatanGame/CatanStatus.h"

#include <functional>

using namespace std;

/*
* NotifyCallback - Notificacion mediante el callback, la respuesta
* de estos llamados siempre es un CatanStatus que identifica
* un posible error o estado.
*/
using NotifyCallback = function<CatanStatus(NetworkPacket*)>;

/*
* SendCallback - Transmision de mensajes a traves del handler
* correspondiente.
*/
using SendCallback = function<void(NetworkPacket*)>;

/*
* ProtocolStatus - Verificacion de ejecucion del protocolo
* para cada estado al implementar las llamadas.
*/
enum class ProtocolStatus : unsigned int {OK, DONE, ERROR};

/*
* ProtocolState
* Modelizacion de un estado del protocolo en el cual se espera 
* resolver el siguiente paso dentro de una comunicacion, ya sea
* recibiendo, enviando o ejecutando alguna accion dentro del mismo
* estado
*/
class ProtocolState {
public:

	/*
	* ProtocolState
	* Se permite construir un estado del protocol con o sin,
	* callback de notificacion y con callback para mandar mensaje.
	*/
	ProtocolState(NotifyCallback notify, SendCallback send);
	ProtocolState(NotifyCallback callback);
	ProtocolState(SendCallback send);
	ProtocolState(void);
	virtual ~ProtocolState();

	/*
	* notify
	* Notifica en caso de tenerlo habilitado, y devuelve estado
	* o resultado, llamando el callback.
	*/
	CatanStatus notify(NetworkPacket* packet);

	/*
	* shouldNotify
	* Devuelve si debe o no notificar la ejecucion del estado
	*/
	bool shouldNotify(void) const;

	/*
	* setSendCallback
	* Configura el callback para transmision de mensajes
	*/
	void setSendCallback(SendCallback send);

	/*
	* canSend
	* Indica si tiene o no configurado callback para mandar mensajes.
	*/
	bool canSend(void) const;

	/*
	* sendPacket
	* Permite mandar un mensaje o paquete de datos
	* utilizando el callback para ello.
	*/
	void sendPacket(NetworkPacket* packet);

	/*
	* Rutinas de operacion del estado de un protocolo.
	* El estado de un protocolo puede redefinir la reaccion
	* ante la necesidad de mandar, haber recibido un mensaje,
	* o bien "solve", una ejecucion inicial al entrar al estado.
	*/
	virtual ProtocolStatus send(NetworkPacket* packet) = 0;
	virtual ProtocolStatus recv(NetworkPacket* packet) = 0;
	virtual ProtocolStatus solve(void) = 0;

private:
	NotifyCallback notifyCallback;
	bool hasNotify;

	SendCallback sendCallback;
	bool hasSend;
};