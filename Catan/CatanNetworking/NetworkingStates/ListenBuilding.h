#pragma once

#include "HandshakingState.h"

class ListenBuilding : public HandshakingState {
public:
	ListenBuilding(CatanNetworking& net) : HandshakingState(listenBuildingProtocol, net, CatanNetworking::States::LISTEN_BUILDING) {}
	virtual bool isHeader(PacketHeader header) { return header == PacketHeader::CITY || header == PacketHeader::ROAD || header == PacketHeader::SETTLEMENT; }
private:
	/* Metodos del protocolo */
	void getBuilding(NetworkPacket* packet) { networking.getGame().handle(packet); }

	/* Protocolo */
	Protocol* listenBuildingProtocol = protocol(
		socket_send(networking.getSocket()),
		"WAIT_BUILD",
		p_recv("WAIT_BUILD", tag("ACK"), bind(&ListenBuilding::getBuilding, this, _1), {PacketHeader::CITY, PacketHeader::ROAD, PacketHeader::SETTLEMENT}),
		p_send("ACK", tag(PROTOCOL_DONE), PacketHeader::ACK)
	);
};