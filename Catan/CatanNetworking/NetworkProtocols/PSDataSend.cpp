#include "PSDataSend.h"

PSDataSend::
PSDataSend(ProtocolTag* tag, NotifyCallback _notify, PacketCallback _callback) : ProtocolState(tag, _notify), callback(_callback) {}

PSDataSend::
PSDataSend(ProtocolTag* tag, PacketCallback _callback) : ProtocolState(tag), callback(_callback) {}

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