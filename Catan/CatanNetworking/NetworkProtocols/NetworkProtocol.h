#pragma once

#include "Protocol.h"
#include "ProtocolState.h"

#include "PSRecv.h"
#include "PSSend.h"
#include "PSRespond.h"

/* Macros para creacion de protocolos */
#define RESPOND(_header)	new PSRespond(_header)
#define SEND(...)			GET_SEND(__VA_ARGS__, N_SEND, S_SEND)(__VA_ARGS__)
#define RECV(...)			GET_RECV(__VA_ARGS__, N_RECV, S_RECV)(__VA_ARGS__)

#define GET_SEND(_1, _2, SNAME, ...) SNAME
#define S_SEND(_headers)			new PSSend(_headers)
#define N_SEND(_notify, _headers)	new PSSend(_notify, _headers)

#define GET_RECV(_1, _2, RNAME, ...) RNAME
#define S_RECV(_headers)			new PSRecv(_headers)
#define N_RECV(_notify, _headers)	new PSRecv(_notify, _headers)