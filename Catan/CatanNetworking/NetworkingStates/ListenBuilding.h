#pragma once

#include "HandshakingState.h"

class ListenBuilding : public HandshakingState {
public:
	ListenBuilding(CatanNetworking& net);
private:
	void getBuilding(NetworkPacket* packet);
};