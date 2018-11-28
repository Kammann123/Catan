#pragma once

#include "HandshakingState.h"

class TellOffer : public HandshakingState {
public:
	TellOffer(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void tradeAnswer(NetworkPacket* packet);
};