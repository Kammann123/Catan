#include "PSSend.h"

PSSend::
PSSend(ProtocolTag* tag, PacketHeader _header) : ProtocolState(tag, ProtocolType::TELLER), header(_header) {}

ProtocolStatus
PSSend::send(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSSend::recv(NetworkPacket* packet) {
	return ProtocolStatus::PROTOCOL_ERROR;
}

ProtocolStatus
PSSend::solve(void) {
	NetworkPacket* packet = new NetworkPacket(header);

	sendPacket(packet);

	return ProtocolStatus::DONE;
}

bool
PSSend::isHeader(PacketHeader header) {
	return header == this->header;
}

bool
PSSend::isHeader(PacketHeader header, ProtocolState::ProtocolType asWhat) {
	return header == this->header && asWhat == type;
}