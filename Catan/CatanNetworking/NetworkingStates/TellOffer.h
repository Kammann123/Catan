#pragma once

#include "HandshakingState.h"

class TellOffer : public HandshakingState {
public:
	TellOffer(CatanNetworking& net);
private:
	void tradeAnswer(NetworkPacket* packet);
};