#include "PSRecv.h"

PSRecv::
PSRecv(ProtocolTag* tag, NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(tag, notify), expected(_expected) {}

PSRecv::
PSRecv(ProtocolTag* tag, NotifyCallback notify, PacketHeader _expected) : ProtocolState(tag, notify) {
	expected.push_back(_expected);
}

PSRecv::
PSRecv(ProtocolTag* tag, list<PacketHeader> _expected) : ProtocolState(tag), expected(_expected) {}

PSRecv::
PSRecv(ProtocolTag* tag, PacketHeader _expected) : ProtocolState(tag) {
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

ProtocolState::ProtocolType
PSRecv::getType(void) {
	return ProtocolType::LISTENER;
}

bool
PSRecv::isHeader(PacketHeader header) {
	return find(expected.begin(), expected.end(), header) != expected.end();
}