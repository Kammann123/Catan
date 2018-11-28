#include "ListenOffer.h"

ListenOffer::
ListenOffer(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_OFFER) {

	/* Definicion del protocolo y configuracion de la misma */
	Protocol* listenOfferProtocol = protocol(
		socket_send(networking.getSocket()),
		"RECV_OFFER",
		p_recv("RECV_OFFER", tag("ANSWER"), bind(&ListenOffer::getOffer, this, _1), PacketHeader::OFFER_TRADE),
		p_wait_send("ANSWER", tag(PROTOCOL_DONE), { PacketHeader::YES, PacketHeader::NO })
	);
	this->setProtocol(listenOfferProtocol);
}

bool 
ListenOffer::isHeader(PacketHeader header) { 
	return header == PacketHeader::OFFER_TRADE; 
}

void 
ListenOffer::getOffer(NetworkPacket* packet) {
	networking.getGame().handle(packet); 
}