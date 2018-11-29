#include "TellQuit.h"

TellQuit::
TellQuit(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_QUIT) {
	/* Defino el protocolo */
	Protocol * tellQuitProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"SEND_QUIT",
		TIMEOUT_TIME,
		p_send("SEND_QUIT", tag("ACK"), PacketHeader::QUIT),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellQuitProtocol);
}