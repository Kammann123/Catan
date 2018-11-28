#include "TellBank.h"

TellBank::
TellBank(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_BANK) {
	/* Defino el protocolo */ 
	Protocol * tellBankProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_BANK",
		p_wait_send("SEND_BANK", tag("ACK"), PacketHeader::BANK_TRADE),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellBankProtocol);
}

bool
TellBank::isHeader(PacketHeader header) {
	return header == PacketHeader::BANK_TRADE;
}