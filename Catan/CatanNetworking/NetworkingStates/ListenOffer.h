#pragma once

#include "HandshakingState.h"

class ListenOffer : public HandshakingState {
public:
	ListenOffer(CatanNetworking& net) : HandshakingState(listenOfferProtocol, net, CatanNetworking::States::LISTEN_OFFER) {}
	string what(void) { return "LISTEN_OFFER"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::OFFER_TRADE;  }
private:
	/* Metodos del protocolo */
	void getOffer(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol* listenOfferProtocol = protocol(
		socket_send(networking.getSocket()),
		"RECV_OFFER",
		p_recv("RECV_OFFER", tag("ANSWER"), bind(&ListenOffer::getOffer, this, _1), PacketHeader::OFFER_TRADE),
		p_wait_send("ANSWER", tag(PROTOCOL_DONE), { PacketHeader::YES, PacketHeader::NO })
	);
};