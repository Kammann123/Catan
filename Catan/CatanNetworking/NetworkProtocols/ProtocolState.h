#pragma once

#include "../NetworkPackets/NetworkPacket.h"
#include "../NetworkHandlers/NetworkSocket.h"
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
	* ProtocolType - Se define un tipo de protocol state y protocol
	* para definir si tanto el estado como el comienzo del protocolo esta definido
	* como de emision o recepcion de mensaje, para manejar dinamicamente o virtualmente
	* el dispatch de los mensajes
	*/
	enum ProtocolType : unsigned int {LISTENER, TELLER, BOTH};

	/*
	* ProtocolState
	* Se permite construir un estado del protocol con o sin,
	* callback de notificacion y con callback para mandar mensaje.
	*/
	ProtocolState(ProtocolTag* tag, NotifyCallback notify, NetworkSocket** socket, ProtocolType _type);
	ProtocolState(ProtocolTag* tag, NotifyCallback callback, ProtocolType _type);
	ProtocolState(ProtocolTag* tag, ProtocolType _type);
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
	* setSocket
	* Configura el socket para mandar los mensajes
	*/
	virtual void setSocket(NetworkSocket** socket);

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
	* getType
	* Devuelve el tipo de estado de protocol, para saber si 
	* debe recibir, mandar o puede ser cualquiera de las dos.
	*/
	ProtocolType getType(void);

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
	virtual bool isHeader(PacketHeader header) = 0;
	virtual bool isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) = 0;
	virtual map<string, ProtocolState*>* getSubStates(void);

protected:
	ProtocolTag* tag;

	NetworkSocket** socket;
	ProtocolType type;
	NotifyCallback notifyCallback;
	bool hasNotify;
};