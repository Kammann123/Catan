#include "PSRespond.h"

PSRespond::
PSRespond(PacketHeader _header) : ProtocolState(), header(_header) {}

ProtocolStatus
PSRespond::send(NetworkPacket* packet) {
	return ProtocolStatus::ERROR;
}

ProtocolStatus
PSRespond::recv(NetworkPacket* packet) {
	return ProtocolStatus::ERROR;
}

ProtocolStatus
PSRespond::solve(void) {
	NetworkPacket* packet = new NetworkPacket(header);

	sendPacket(packet);

	return ProtocolStatus::DONE;
}