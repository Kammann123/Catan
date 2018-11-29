#include "TellBank.h"

TellBank::
TellBank(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_BANK) {
	/* Defino el protocolo */ 
	Protocol * tellBankProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"SEND_BANK",
		TIMEOUT_TIME,
		p_wait_send("SEND_BANK", tag("ACK"), PacketHeader::BANK_TRADE),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellBankProtocol);
}