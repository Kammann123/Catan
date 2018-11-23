#pragma once

#include "Protocol.h"
#include "ProtocolState.h"

#include "PSRecv.h"
#include "PSWaitSend.h"
#include "PSDataSend.h"
#include "PSSend.h"

/* Macros para creacion de protocolos 
*
* Ejemplo de uso:
*
* Protocol myProtocol(
*		sendCallback, 
*		{
*			SEND('NAME'),
*			RECV(setName, 'NAME_IS'),
*			SEND('ACK')
*		}
* );
*/
#define SEND(_header)	new PSSend(_header)
#define WAIT_SEND(...)		GET_WAIT_SEND(__VA_ARGS__, N_WAIT_SEND, S_WAIT_SEND)(__VA_ARGS__)
#define DATA_SEND(...)		GET_DATA_SEND(__VA__ARGS, N_DATA_SEND, S_DATA_SEND)(__VA_ARGS__)
#define RECV(...)			GET_RECV(__VA_ARGS__, N_RECV, S_RECV)(__VA_ARGS__)

/* Definiciones bajo nivel de estados de protocolo
* para una mejor definicion de la sintaxis de uso en
* la creacion de los protocolo...
*/
#define GET_DATA_SEND(_1, _2, DS_NAME, ...) DS_NAME
#define S_DATA_SEND(_callback)	new PSDataSend(_callback)
#define N_DATA_SEND(_notify, _callback) new PSDataSend(_notify, _callback)

#define GET_WAIT_SEND(_1, _2, WS_NAME, ...) WS_NAME
#define S_WAIT_SEND(_headers)			new PSWaitSend(_headers)
#define N_WAIT_SEND(_notify, _headers)	new PSWaitSend(_notify, _headers)

#define GET_RECV(_1, _2, RNAME, ...) RNAME
#define S_RECV(_headers)			new PSRecv(_headers)
#define N_RECV(_notify, _headers)	new PSRecv(_notify, _headers)