#pragma once

#include "../NetworkPackets/NetworkPacket.h"
#include "../../CatanGame/CatanStatus.h"
#include "ProtocolTag.h"

#include <functional>
#include <map>
#include <string>

using namespace std;

/*
* NotifyCallback - Notificacion mediante el callback, la respuesta
* de estos llamados siempre es un CatanStatus que identifica
* un posible error o estado.
*/
using NotifyCallback = function<void(NetworkPacket*)>;

/*
* SendCallback - Transmision de mensajes a traves del handler
* correspondiente.
*/
using SendCallback = function<void(NetworkPacket*)>;

/*
* ProtocolStatus - Verificacion de ejecucion del protocolo
* para cada estado al implementar las llamadas.
*/
enum class ProtocolStatus : unsigned int {OK, DONE, PROTOCOL_ERROR, TIMEOUT};

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
	ProtocolState(ProtocolTag* tag, NotifyCallback notify, SendCallback send);
	ProtocolState(ProtocolTag* tag, NotifyCallback callback);
	ProtocolState(ProtocolTag* tag);
	virtual ~ProtocolState();

	/*
	* setNotifyCallback
	* Permite configurar el notify callback
	*/
	void setNotifyCallback(NotifyCallback notify);
	NotifyCallback getNotifyCallback(void);

	/*
	* notify
	* Notifica en caso de tenerlo habilitado, y devuelve estado
	* o resultado, llamando el callback.
	*/
	void notify(NetworkPacket* packet);

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
	* getNextTag
	* Devuelve el siguiente tag del estado del protocolo
	*/
	string getNextTag(void);
	ProtocolTag* getTag(void);

	/*
	* Rutinas de operacion del estado de un protocolo.
	* El estado de un protocolo puede redefinir la reaccion
	* ante la necesidad de mandar, haber recibido un mensaje,
	* o bien "solve", una ejecucion inicial al entrar al estado.
	*/
	virtual ProtocolStatus send(NetworkPacket* packet) = 0;
	virtual ProtocolStatus recv(NetworkPacket* packet) = 0;
	virtual ProtocolStatus solve(void) = 0;
	virtual map<string, ProtocolState*>* getSubStates(void);

protected:
	ProtocolTag* tag;
	NotifyCallback notifyCallback;
	SendCallback sendCallback;
	bool hasNotify;
	bool hasSend;
};