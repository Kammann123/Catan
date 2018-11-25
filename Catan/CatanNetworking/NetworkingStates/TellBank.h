#pragma once

#include "HandshakingState.h"

class TellBank : public HandshakingState {
public:
	TellBank(CatanNetworking& net) : HandshakingState(tellBankProtocol, net) {}
	string what(void) { return "TELL_BANK"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::BANK_TRADE;  }
private:
	/* Protocolo */
	Protocol * tellBankProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_BANK",
		p_wait_send("SEND_BANK", tag("ACK"), PacketHeader::BANK_TRADE),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};