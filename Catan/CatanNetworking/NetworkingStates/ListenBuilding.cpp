#include "ListenBuilding.h"

ListenBuilding::
ListenBuilding(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::LISTEN_BUILDING) {

	/* Creo el protocolo en cuestion y lo configuro al handler */
	Protocol* listenBuildingProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"WAIT_BUILD",
		TIMEOUT_TIME,
		p_recv("WAIT_BUILD", tag("ACK"), bind(&ListenBuilding::getBuilding, this, _1), { PacketHeader::CITY, PacketHeader::ROAD, PacketHeader::SETTLEMENT }),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(listenBuildingProtocol);
}

void
ListenBuilding::getBuilding(NetworkPacket* packet) { 
	networking.getGame().handle(packet);
}