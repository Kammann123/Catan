#pragma once

#include "HandshakingState.h"

class ListenDices : public HandshakingState {
public:
	ListenDices(CatanNetworking& net) : HandshakingState(listenDicesProtocol, net, CatanNetworking::States::LISTEN_DICES) {}
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::PASS; }
private:
	/* Metodos del protocolo */
	unsigned int decideRobber(void) { 
		if (networking.getGame().isRobberStatus()) {
			if (networking.getGame().hasRobberCards(PlayerId::PLAYER_ONE)) {
				return 1;
			}
			return 2;
		}
		return 0;
	}

	void setDices(NetworkPacket* packet) { networking.getGame().handle(packet); }
	void setRemoteCards(NetworkPacket* packet) { networking.getGame().handle(packet); }
	void setRobberMove(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol* listenDicesProtocol = protocol(
		socket_send(networking.getSocket()),
		"PASS",
		p_wait_send("PASS", tag("RECV_DICES"), PacketHeader::PASS), 
		p_recv("RECV_DICES", list_tag(bind(&ListenDices::decideRobber, this), { "DICES_ACK", "SEND_CARDS", "WAIT_CARDS" }), bind(&ListenDices::setDices, this, _1), PacketHeader::DICES_ARE),
		p_wait_send("SEND_CARDS", tag("SEND_ACK"), PacketHeader::ROBBER_CARDS),
		p_send("WAIT_CARDS", tag("SEND_ACK"), PacketHeader::ACK),
		p_if_recv("SEND_ACK",
			p_recv("REMOVE_MOVE", tag("DICES_ACK"), bind(&ListenDices::setRobberMove, this, _1), PacketHeader::ROBBER_MOVE),
			p_recv("REMOTE_CARDS", tag("REMOTE_ACK"), bind(&ListenDices::setRemoteCards, this, _1), PacketHeader::ROBBER_CARDS)
		),
		p_send("REMOTE_ACK", tag("REMOTE_MOVE"), PacketHeader::ACK),
		p_send("DICES_ACK", tag(PROTOCOL_DONE), ACK)
	);
};