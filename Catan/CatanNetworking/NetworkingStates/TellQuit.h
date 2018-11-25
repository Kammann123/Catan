#pragma once

#include "HandshakingState.h"

class TellQuit : public HandshakingState {
public:
	TellQuit(CatanNetworking& net) : HandshakingState(tellQuitProtocol, net) {}
	string what(void) { return "TELL_QUIT"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::QUIT; }
private:
	/* Protocolo */
	Protocol * tellQuitProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_QUIT",
		p_send("SEND_QUIT", tag("ACK"), PacketHeader::QUIT),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};