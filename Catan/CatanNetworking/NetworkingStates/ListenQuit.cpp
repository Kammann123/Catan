#include "ListenQuit.h"

ListenQuit::
ListenQuit(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_QUIT) {
	/* Definicion del protocolo */
	Protocol* listenQuitProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_QUIT",
		p_recv("WAIT_QUIT", tag("ACK"), { PacketHeader::QUIT }),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenQuitProtocol);
}

bool 
ListenQuit::isHeader(PacketHeader header) {
	return header == PacketHeader::QUIT;
}

void 
ListenQuit::setQuit(NetworkPacket* packet) { 
	networking.getGame().handle(new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_TWO)); 
}