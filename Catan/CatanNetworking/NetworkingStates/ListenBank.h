#pragma once

#include "HandshakingState.h"

class ListenBank : public HandshakingState {
public:
	ListenBank(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void getBank(NetworkPacket* packet);
};