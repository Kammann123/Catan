#pragma once

#include "HandshakingState.h"

class TellOffer : public HandshakingState {
public:
	TellOffer(CatanNetworking& net) : HandshakingState(tellOfferProtocol, net) {}
	string what(void) { return "TELL_OFFER"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::OFFER_TRADE; }
private:
	/* Metodos del protocolo */
	void tradeAnswer(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol* tellOfferProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_OFFER",
		p_wait_send("SEND_OFFER", tag("ANSWER"), PacketHeader::OFFER_TRADE),
		p_recv("ANSWER", tag(PROTOCOL_DONE), bind(&TellOffer::tradeAnswer, this, _1), { PacketHeader::YES, PacketHeader::NO })
	);
};