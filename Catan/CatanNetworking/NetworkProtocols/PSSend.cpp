#include "PSSend.h"

PSSend::
PSSend(NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(notify), expected(_expected) {}

PSSend::
PSSend(list<PacketHeader> _expected) : ProtocolState(), expected(_expected) {}

ProtocolStatus
PSSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::ERROR;
}

ProtocolStatus
PSSend::send(NetworkPacket* packet) {
	/* Recibio un mensaje no esperado? */
	if (find(expected.begin(), expected.end(), packet->getHeader()) == expected.end()) {
		return ProtocolStatus::ERROR;
	}
	else {

		/* Envio el mensaje */
		sendPacket(packet);

		return ProtocolStatus::DONE;
	}
}

ProtocolStatus
PSSend::solve(void) {
	return ProtocolStatus::OK;
}
