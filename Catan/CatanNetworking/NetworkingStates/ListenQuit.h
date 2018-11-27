#pragma once

#include "HandshakingState.h"

class ListenQuit : public HandshakingState {
public:
	ListenQuit(CatanNetworking& net) : HandshakingState(listenQuitProtocol, net, CatanNetworking::States::LISTEN_QUIT) {}
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::QUIT; }
private:
	/* Metodos del protocolo */
	void setQuit(NetworkPacket* packet) { networking.getGame().handle(new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); }
	/* Protocolo */
	Protocol* listenQuitProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_QUIT",
		p_recv("WAIT_QUIT", tag("ACK"), { PacketHeader::QUIT }),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};