#pragma once

#include "HandshakingState.h"

class TellBuilding : public HandshakingState {
public:
	TellBuilding(CatanNetworking& net) : HandshakingState(tellBuildingProtocol, net, CatanNetworking::States::TELL_BUILDING) {}
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::ROAD || header == PacketHeader::CITY || header == PacketHeader::SETTLEMENT;  }
private:
	/* Protocolo */
	Protocol * tellBuildingProtocol = protocol(
		socket_send(networking.getSocket()),
		"SEND_BUILD",
		p_wait_send("SEND_BUILD", tag("ACK"), {PacketHeader::ROAD, PacketHeader::CITY, PacketHeader::SETTLEMENT}),
		p_recv("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};