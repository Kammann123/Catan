#include "PSRecv.h"

PSRecv::
PSRecv(ProtocolTag* tag, NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(tag, notify, ProtocolType::LISTENER), expected(_expected) {}

PSRecv::
PSRecv(ProtocolTag* tag, NotifyCallback notify, PacketHeader _expected) : ProtocolState(tag, notify, ProtocolType::LISTENER) {
	expected.push_back(_expected);
}

PSRecv::
PSRecv(ProtocolTag* tag, list<PacketHeader> _expected) : ProtocolState(tag, ProtocolType::LISTENER), expected(_expected) {}

PSRecv::
PSRecv(ProtocolTag* tag, PacketHeader _expected) : ProtocolState(tag, ProtocolType::LISTENER) {
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

bool
PSRecv::isHeader(PacketHeader header) {
	return find(expected.begin(), expected.end(), header) != expected.end();
}

bool
PSRecv::isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) {
	return find(expected.begin(), expected.end(), header) != expected.end() && asWhat == type;
}