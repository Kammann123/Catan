#include "PSWaitSend.h"

PSWaitSend::
PSWaitSend(NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(notify), expected(_expected) {}

PSWaitSend::
PSWaitSend(NotifyCallback notify, PacketHeader _expected) : ProtocolState(notify) {
	expected.push_back(_expected);
}

PSWaitSend::
PSWaitSend(list<PacketHeader> _expected) : ProtocolState(), expected(_expected) {}

PSWaitSend::
PSWaitSend(PacketHeader _expected) : ProtocolState() {
	expected.push_back(_expected);
}

ProtocolStatus
PSWaitSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSWaitSend::send(NetworkPacket* packet) {
	/* Recibio un mensaje no esperado? */
	if (find(expected.begin(), expected.end(), packet->getHeader()) == expected.end()) {
		return ProtocolStatus::PROTOCOL_ERROR;
	}
	else {

		/* Envio el mensaje */
		sendPacket(packet);

		return ProtocolStatus::DONE;
	}
}

ProtocolStatus
PSWaitSend::solve(void) {
	return ProtocolStatus::OK;
}
