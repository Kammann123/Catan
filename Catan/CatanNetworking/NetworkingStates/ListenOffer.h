#pragma once

#include "HandshakingState.h"

class ListenOffer : public HandshakingState {
public:
	ListenOffer(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void getOffer(NetworkPacket* packet);
};