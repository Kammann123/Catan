#include "PSRecv.h"

PSRecv::
PSRecv(NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(notify), expected(_expected) {}

PSRecv::
PSRecv(NotifyCallback notify, PacketHeader _expected) : ProtocolState(notify) {
	expected.push_back(_expected);
}

PSRecv::
PSRecv(list<PacketHeader> _expected) : ProtocolState(), expected(_expected) {}

PSRecv::
PSRecv(PacketHeader _expected) : ProtocolState() {
	expected.push_back(_expected);
}

ProtocolStatus
PSRecv::send(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSRecv::recv(NetworkPacket* packet) {
	/* Recibio un mensaje no esperado? */
	if (find(expected.begin(), expected.end(), packet->getHeader()) == expected.end()) {
		return ProtocolStatus::PROTOCOL_ERROR;
	}
	else {
		return ProtocolStatus::DONE;
	}
}

ProtocolStatus
PSRecv::solve(void) {
	return ProtocolStatus::OK;
}