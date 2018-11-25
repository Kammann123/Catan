#pragma once

#include "HandshakingState.h"

class TellDices : public HandshakingState {
public:
	TellDices(CatanNetworking& net) : HandshakingState(tellDicesProtocol, net) {}
	string what(void) { return "TELL_DICES"; }
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::PASS;  }
private:
	/* Metodos del protocolo */
	bool isRobber(void) { return true; /* PREGUNTAR AL JUEGO SI ES MODO ROBBER */ }
	void remoteRobberCards(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol * tellDicesProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_PASS",
		p_recv("WAIT_PASS", tag("SEND_DICES"), PacketHeader::PASS),
		p_wait_send("SEND_DICES", cond_tag(bind(&TellDices::isRobber, this), "REMOTE_CARDS", "DICES_ACK"), PacketHeader::DICES_ARE),
		p_if_recv("REMOTE_CARDS",
			p_recv("REMOTE_ROBBER", tag("LOCAL_ROBBER"), bind(&TellDices::remoteRobberCards, this, _1), PacketHeader::ROBBER_CARDS),
			p_recv("REMOTE_ACK", tag("LOCAL_ROBBER"), PacketHeader::ACK)
		),
		p_if_send("LOCAL_ROBBER",
			p_wait_send("LOCAL_CARDS", tag("CARDS_ACK"), PacketHeader::ROBBER_CARDS),
			p_wait_send("LOCAL_MOVE", tag("DICES_ACK"), PacketHeader::ROBBER_MOVE)
		),
		p_recv("CARDS_ACK", tag("LOCAL_MOVE"), PacketHeader::ACK),
		p_recv("DICES_ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};