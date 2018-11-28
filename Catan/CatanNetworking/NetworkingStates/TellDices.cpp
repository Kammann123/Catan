#include "TellDices.h"

TellDices::
TellDices(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_DICES) {
	/* Defino el protocolo */
	Protocol * tellDicesProtocol = protocol(
		socket_send(networking.getSocket()),
		"PASS_OR_DICES",
		p_if("PASS_OR_DICES", 
			p_recv("WAIT_PASS", tag("SEND_DICES"), PacketHeader::PASS),
			p_wait_send("SEND_DICES", cond_tag(bind(&TellDices::isRobber, this), "REMOTE_CARDS", "DICES_ACK"), PacketHeader::DICES_ARE)
		),
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
	this->setProtocol(tellDicesProtocol);
}

bool 
TellDices::isRobber(void) { 
	return networking.getGame().isRobberStatus();
}

void 
TellDices::remoteRobberCards(NetworkPacket* packet) { 
	networking.getGame().handle(packet); 
}