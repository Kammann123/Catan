#include "TellQuit.h"

TellQuit::
TellQuit(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_QUIT) {
	/* Defino el protocolo */
	Protocol * tellQuitProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_QUIT",
		p_send("SEND_QUIT", tag("ACK"), PacketHeader::QUIT),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellQuitProtocol);
}

bool
TellQuit::isHeader(PacketHeader header) {
	return header == PacketHeader::QUIT;
}