#pragma once

#include "HandshakingState.h"

class ListenBuilding : public HandshakingState {
public:
	ListenBuilding(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void getBuilding(NetworkPacket* packet);
};