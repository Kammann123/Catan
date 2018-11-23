#include "PSDataSend.h"

PSDataSend::
PSDataSend(NotifyCallback _notify, PacketCallback _callback) : ProtocolState(_notify), callback(_callback) {}

PSDataSend::
PSDataSend(PacketCallback _callback) : ProtocolState(), callback(_callback) {}

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