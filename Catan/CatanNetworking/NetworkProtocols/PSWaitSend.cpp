#include "PSWaitSend.h"

PSWaitSend::
PSWaitSend(ProtocolTag* tag, NotifyCallback notify, list<PacketHeader> _expected) : ProtocolState(tag, notify, ProtocolType::TELLER), expected(_expected) {}

PSWaitSend::
PSWaitSend(ProtocolTag* tag, NotifyCallback notify, PacketHeader _expected) : ProtocolState(tag, notify, ProtocolType::TELLER) {
	expected.push_back(_expected);
}

PSWaitSend::
PSWaitSend(ProtocolTag* tag, list<PacketHeader> _expected) : ProtocolState(tag, ProtocolType::TELLER), expected(_expected){}

PSWaitSend::
PSWaitSend(ProtocolTag* tag, PacketHeader _expected) : ProtocolState(tag, ProtocolType::TELLER) {
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

bool
PSWaitSend::isHeader(PacketHeader header) {
	return find(expected.begin(), expected.end(), header) != expected.end();
}