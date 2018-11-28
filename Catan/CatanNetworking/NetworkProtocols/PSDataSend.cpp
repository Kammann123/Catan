#include "PSDataSend.h"

PSDataSend::
PSDataSend(ProtocolTag* tag, NotifyCallback _notify, PacketCallback _callback) : ProtocolState(tag, _notify, ProtocolState::TELLER), callback(_callback) {}

PSDataSend::
PSDataSend(ProtocolTag* tag, PacketCallback _callback) : ProtocolState(tag, ProtocolState::TELLER), callback(_callback) {}

ProtocolStatus
PSDataSend::send(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSDataSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSDataSend::solve(void) {
	NetworkPacket* packet = callback();

	sendPacket(packet);

	return ProtocolStatus::DONE;
}

bool
PSDataSend::isHeader(PacketHeader header) {
	return false;
}

bool
PSDataSend::isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) {
	return false;
}