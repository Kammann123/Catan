#pragma once

#include "HandshakingState.h"

class ListenOffer : public HandshakingState {
public:
	ListenOffer(CatanNetworking& net);
private:
	void getOffer(NetworkPacket* packet);
};