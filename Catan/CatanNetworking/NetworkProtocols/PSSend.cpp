#include "PSSend.h"

PSSend::
PSSend(PacketHeader _header) : ProtocolState(), header(_header) {}

ProtocolStatus
PSSend::send(NetworkPacket* packet) {
	return ProtocolStatus::ERROR;
}

ProtocolStatus
PSSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::ERROR;
}

ProtocolStatus
PSSend::solve(void) {
	NetworkPacket* packet = new NetworkPacket(header);

	sendPacket(packet);

	return ProtocolStatus::DONE;
}