#include "ListenBank.h"

ListenBank::
ListenBank(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_BANK) {

	/* Defino el protocolo en cuestion y luego lo guardo en el padre */
	Protocol* listenBankProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"WAIT_BANK",
		TIMEOUT_TIME,
		p_recv("WAIT_BANK", tag("ACK"), bind(&ListenBank::getBank, this, _1), PacketHeader::BANK_TRADE),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenBankProtocol);
}

void
ListenBank::getBank(NetworkPacket* packet) {
	networking.getGame().handle(packet);
}