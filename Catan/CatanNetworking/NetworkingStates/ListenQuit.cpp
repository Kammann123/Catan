#include "ListenQuit.h"

ListenQuit::
ListenQuit(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_QUIT) {
	/* Definicion del protocolo */
	Protocol* listenQuitProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"WAIT_QUIT",
		TIMEOUT_TIME,
		p_recv("WAIT_QUIT", tag("ACK"), bind(&ListenQuit::setQuit, this, _1), { PacketHeader::QUIT }),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenQuitProtocol);
}

void 
ListenQuit::setQuit(NetworkPacket* packet) {
	confirm(packet);
	networking.getGame().syncHandle(new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO));
}