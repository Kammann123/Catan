#include "ListenBank.h"

ListenBank::
ListenBank(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_BANK) {

	/* Defino el protocolo en cuestion y luego lo guardo en el padre */
	Protocol* listenBankProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_BANK",
		p_recv("WAIT_BANK", tag("ACK"), bind(&ListenBank::getBank, this, _1), PacketHeader::BANK_TRADE),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenBankProtocol);
}

bool
ListenBank::isHeader(PacketHeader header) {
	return header == PacketHeader::BANK_TRADE;
}

void
ListenBank::getBank(NetworkPacket* packet) {
	networking.getGame().handle(packet);
}