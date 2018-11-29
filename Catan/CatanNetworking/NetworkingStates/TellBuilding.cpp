#include "TellBuilding.h"

TellBuilding::
TellBuilding(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_BUILDING) {
	/* Defino el protocolo */
	Protocol * tellBuildingProtocol = timeout_protocol(
		socket_send(networking.getSocket()),
		"SEND_BUILD",
		TIMEOUT_TIME,
		p_wait_send("SEND_BUILD", tag("ACK"), { PacketHeader::ROAD, PacketHeader::CITY, PacketHeader::SETTLEMENT }),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellBuildingProtocol);
}