#pragma once

#include "HandshakingState.h"

class ListenBank : public HandshakingState {
public:
	ListenBank(CatanNetworking& net) : HandshakingState(listenBankProtocol, net, CatanNetworking::States::LISTEN_BANK) {}
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::BANK_TRADE; }
private:
	/* Metodos del protocolo */
	void getBank(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol* listenBankProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_BANK",
		p_recv("WAIT_BANK", tag("ACK"), bind(&ListenBank::getBank, this, _1), PacketHeader::BANK_TRADE),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};