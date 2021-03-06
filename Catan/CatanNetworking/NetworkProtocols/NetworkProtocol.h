#pragma once

#include "Protocol.h"

#include "ProtocolTag.h"
#include "StringTag.h"
#include "ConditionalTag.h"
#include "ListTag.h"

#include "ProtocolState.h"
#include "PSRecv.h"
#include "PSWaitSend.h"
#include "PSDataSend.h"
#include "PSSend.h"
#include "PSIf.h"

#include "../NetworkHandlers/NetworkServer.h"
#include "../NetworkHandlers/NetworkClient.h"

#include <exception>
#include <functional>

using namespace std;
using namespace std::placeholders;

/* Aclarcion de uso - PROTOCOL 
* Una vez creado el protocolo con los macros que aqui se detallaran, debe usted unicamente
* ejecutar 3 acciones segun sea debido en el flujo de su programa. Estas tres se definen en el
* archivo correspondiente de Protocol.h, no obstante, a modo de resumen, se detalla:
*
*	+ Ejecutar el metodo "send": Cuando en su programa sea requerido mandar un paquete.
*	+ Ejecutar el metodo "recv": Cuando en su programa se haya recibido un paquete.
*	+ Revisar el metodo "getStatus": Posterior a send, recv, ejecutar para ver estados de error
*		o funcionamiento correcto.
*
* Buena suerte, que la fuerza este contigo.
*
*/

/* Macros bajo nivel de tags */
#define tag(...)			(ProtocolTag*)new StringTag(__VA_ARGS__)
#define list_tag(...)			(ProtocolTag*)new ListTag(__VA_ARGS__)
#define cond_tag(...)	(ProtocolTag*)new ConditionalTag(__VA_ARGS__)

/* Macros de bajo nivel para estados de protocolo */
#define RECV(...)	new PSRecv(__VA_ARGS__)
#define SEND(...)	new PSSend(__VA_ARGS__)
#define WAIT_SEND(...)	new PSWaitSend(__VA_ARGS__)
#define	DATA_SEND(...)	new PSDataSend(__VA_ARGS__)
#define IF(...)	new PSIf(__VA_ARGS__)

/* Macros de sockets 
*	Macros para facilitar la creacion del callback para mandar mensajes
*	dentro de un protocolo cualquiera, sea que se tiene un server o un client
*/
#define socket_send(_socket)	&_socket

/* Macro para creacion de protocolos 
*
* Posibles creaciones de protocolos, al momento varian en las siguientes formas:
*	- protocol: Permite crear un protocol, con su callback para mandar mensajes, su punto de 
*		inicio en los tags del flujo, y la secuencia de estados.
*		+ protocol( 
*			socket_send(myBeautifulSocket),
*			"NAME",
*			p_recv("REQUEST_NAME", "ANSWER_NAME", NAME),
*			p_data_send("ANSWER_NAME", "WAIT_ACK", getLocalName),
*			p_recv("WAIT_ACK", PROTOCOL_DONE, ACK)
*		)
*
*	- timeout_protocol: Es igual que protocol con un campo mas para definir un valor de timeout
*		pasado el cual se pone el protocolo en estado de error por TIMEOUT. Usa de igual manera.
*		Se mide el timeout en milisegundos.
*		+ timeout_protocol( 
*			socket_send(myBeautifulSocket),
*			"NAME",
*			100,
*			p_recv("REQUEST_NAME", "ANSWER_NAME", NAME),
*			p_data_send("ANSWER_NAME", "WAIT_ACK", getLocalName),
*			p_recv("WAIT_ACK", PROTOCOL_DONE, ACK)
*		)
*
*/
#define timeout_protocol(_callback, _start, _timeout, ...)	new Protocol(_callback, _start, _timeout, {__VA_ARGS__})
#define protocol(_callback, _start, ...)		new Protocol(_callback, _start, {__VA_ARGS__})

/* Macros accesibles y utiles para estados del protocolo
*
* Para el uso correcto de estos MACROS para la creacion de estados de protocolo seguir el
* siguiente esquema
*
*	- recv: Crea un estado de protocolo que espera recibir un mensaje, con los siguientes formatos:
*			+ p_recv("RECV_TAG", tag("NEXT_STATE"), ACK)
+			+ p_recv("RECV_TAG", tag("NEXT_STATE"), callback, ACK)
+			+ p_recv("RECV_TAG", tag("NEXT_STATE"), {ACK, ERROR})
+			+ p_recv("RECV_TAG", tag("NEXT_STATE"), callback, {ACK, ERROR})
*
*		nota: Se indica cual es el tag del estado, como decidir cual es su siguiente tag,
*			se define que tipos de paquetes espera, y un callback para notificar el paquete
*			cuando se recibe.
*
*	- send: Crea un estado de protocolo que manda directamente un mensaje, con los formatos:
*			+ p_send("SEND_TAG", tag("NEXT_STATE"), ACK)
*
*		nota: Se indica cual es el tag del esatdo, como decidir cual es su siguiente tag,
*			y el header del paquete a enviar, notese que es transmision directa,
*			no necesita esperar datos o buscar datos de logica, no obstante, son sin cuerpo.
*
*	- wait_send: Crea un estado de protocolo que manda un mensaje esperando que se lo vengan a 
*			a pedir que lo mande, indicandole cual es el paquete, y tiene los formatos:
*			+ p_wait_send("WAIT_TAG", tag("NEXT_STATE"), DICES_ARE)
*			+ p_wait_send("WAIT_TAG", tag("NEXT_STATE"), callback, DICES_ARE)
*			+ p_wait_send("WAIT_TAG", tag("NEXT_STATE"), {DICES_ARE, ROBBER_CARD})
*			+ p_wait_send("WAIT_TAG", tag("NEXT_STATE"), callback, {DICES_ARE, ROBBER_CARD})
*
*		nota: Se indica cual es el tag del estado, como decidir a que estado pasar, y luego
*			que tipo de paquete es valido que le pidan que mande, y un callback para notificar
*			la transmision si se realizo.
*
*	- data_send: Crea un estado de protocolo que manda un mensaje de forma directa, no obstante
*			busca la informacion del paquete a enviar en un callback dado, y sus formatos:
*			+ p_data_send("DATA_TAG", tag("NEXT_STATE"), callback)
*			+ p_data_send("DATA_TAG", tag("NEXT_STATE"), notify, callback)
*
*		nota: Se indica su tag de estado, como decidir el proximo tag de estado, y luego
*			se informa si se quiere un callback para notificar ejecucion del estado y tambien
*			un callback para poder buscar el paquete de datos a enviar
*
*	- if_recv: Crea un estado de protocolo que puede recibir multiples respuestas y para cada una
*			realizar una notificacion o una bifurcacion del protocolo, sus formatos:
*			+ p_if_recv("RECV_MULT_TAG", 
*						recv("FIRST_RECV", "FIRST_NEXT", ACK),
*						recv("SECOND_RECV", "SECOND_NEXT", ROBBER_CARDS)
*					)
*					
*		nota: Se indica el tag que define al estado y luego cada uno de los posibles admitidos
*			se define consecutivamente con varios recv
*
*	- if_send: Crea un esatdo de protocolo que puede esperar mandar multiples respuestas y 
*			donde son todas de tipo wait_data, es decir, espera que alguien le pida mandar
*			un paquete dado, y valida que sea ese el paquete correcto, creando diferentes
*			flujos del protocolo, sus formatos son:
*			+ p_if_send("SEND_MULT_TAG", 
*						wait_send("FIRST_TAG", tag("FIRST_STATE"), ROBBER_CARDS),
*						wait_send("SCND_TAG", tag("SCND_STATE"), ROBBER_MOVE)
*					)
*
* NOTA: El p_if, p_if_send, p_if_recv, son todo lo mismo, bien podria haber solamente un p_if,
*	pero se mantiene disponible el send/recv ante unas modificaciones que se hicieron, con lo que cual
*	se busca mantener la compatibilidad con lo previamente hecho.
*
*/
#define p_recv(_tag, ...)			{_tag, RECV(__VA_ARGS__)}
#define p_send(_tag, ...)			{_tag, SEND(__VA_ARGS__)}
#define p_wait_send(_tag, ...)	{_tag, WAIT_SEND(__VA_ARGS__)}
#define p_data_send(_tag, ...)	{_tag, DATA_SEND(__VA_ARGS__)}
#define p_if_recv(_tag, ...)		{_tag, IF({__VA_ARGS__})}
#define p_if_send(_tag, ...)		{_tag, IF({__VA_ARGS__})}
#define p_if(_tag, ...)				{_tag, IF({__VA_ARGS__})}