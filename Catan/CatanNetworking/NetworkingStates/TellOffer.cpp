#include "TellOffer.h"

TellOffer::
TellOffer(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_OFFER) {
	/* Defino el protocolo */
	Protocol* tellOfferProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"SEND_OFFER",
		TIMEOUT_TIME,
		p_wait_send("SEND_OFFER", tag("ANSWER"), PacketHeader::OFFER_TRADE),
		p_recv("ANSWER", tag(PROTOCOL_DONE), bind(&TellOffer::tradeAnswer, this, _1), { PacketHeader::YES, PacketHeader::NO })
	);
	this->setProtocol(tellOfferProtocol);
}

void 
TellOffer::tradeAnswer(NetworkPacket* packet) {
	confirm(packet);
	networking.getGame().syncHandle(packet);
}