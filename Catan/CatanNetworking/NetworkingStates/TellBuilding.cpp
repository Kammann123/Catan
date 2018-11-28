#include "TellBuilding.h"

TellBuilding::
TellBuilding(CatanNetworking& net) : HandshakingState(net, CatanNetworking::States::TELL_BUILDING) {
	/* Defino el protocolo */
	Protocol * tellBuildingProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_BUILD",
		p_wait_send("SEND_BUILD", tag("ACK"), { PacketHeader::ROAD, PacketHeader::CITY, PacketHeader::SETTLEMENT }),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
	this->setProtocol(tellBuildingProtocol);
}