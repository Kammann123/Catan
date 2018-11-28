#include "ListenDices.h"

ListenDices::
ListenDices(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_DICES) {

	/* Defino el protocolo en cuestion y lo configuro */
	Protocol* listenDicesProtocol = protocol(
		socket_send(networking.getSocket()),
		"PASS_OR_DICES",
		p_if("PASS_OR_DICES",
			p_wait_send("PASS", tag("RECV_DICES"), PacketHeader::PASS),
			p_recv("RECV_DICES", list_tag(bind(&ListenDices::decideRobber, this), { "DICES_ACK", "SEND_CARDS", "WAIT_CARDS" }), bind(&ListenDices::setDices, this, _1), PacketHeader::DICES_ARE)
		),
		p_wait_send("SEND_CARDS", tag("SEND_ACK"), PacketHeader::ROBBER_CARDS),
		p_send("WAIT_CARDS", tag("SEND_ACK"), PacketHeader::ACK),
		p_if_recv("SEND_ACK",
			p_recv("REMOVE_MOVE", tag("DICES_ACK"), bind(&ListenDices::setRobberMove, this, _1), PacketHeader::ROBBER_MOVE),
			p_recv("REMOTE_CARDS", tag("REMOTE_ACK"), bind(&ListenDices::setRemoteCards, this, _1), PacketHeader::ROBBER_CARDS)
		),
		p_send("REMOTE_ACK", tag("REMOTE_MOVE"), PacketHeader::ACK),
		p_send("DICES_ACK", tag(PROTOCOL_DONE), ACK)
	);
	this->setProtocol(listenDicesProtocol);
}

unsigned int 
ListenDices::decideRobber(void) {
	if (networking.getGame().isRobberStatus()) {
		if (networking.getGame().hasRobberCards(PlayerId::PLAYER_ONE)) {
			return 1;
		}
		return 2;
	}
	return 0;
}

void 
ListenDices::setDices(NetworkPacket* packet) { 
	networking.getGame().handle(packet); 
}

void 
ListenDices::setRemoteCards(NetworkPacket* packet) { 
	networking.getGame().handle(packet); 
}

void 
ListenDices::setRobberMove(NetworkPacket* packet) {
	networking.getGame().handle(packet); 
}

bool
ListenDices::isHeader(PacketHeader header) {
	return header == PacketHeader::PASS || header == PacketHeader::DICES_ARE;
}