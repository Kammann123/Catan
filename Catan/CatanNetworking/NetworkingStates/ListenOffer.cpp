#include "ListenOffer.h"

ListenOffer::
ListenOffer(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_OFFER) {

	/* Definicion del protocolo y configuracion de la misma */
	Protocol* listenOfferProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"RECV_OFFER",
		TIMEOUT_TIME,
		p_recv("RECV_OFFER", tag("ANSWER"), bind(&ListenOffer::getOffer, this, _1), PacketHeader::OFFER_TRADE),
		p_wait_send("ANSWER", tag(PROTOCOL_DONE), { PacketHeader::YES, PacketHeader::NO })
	);
	this->setProtocol(listenOfferProtocol);
}

void 
ListenOffer::getOffer(NetworkPacket* packet) {
	networking.getGame().handle(packet); 
}