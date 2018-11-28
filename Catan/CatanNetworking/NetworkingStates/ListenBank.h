#pragma once

#include "HandshakingState.h"

class ListenBank : public HandshakingState {
public:
	ListenBank(CatanNetworking& net);
private:
	void getBank(NetworkPacket* packet);
};