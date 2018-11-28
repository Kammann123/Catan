#pragma once

#include "HandshakingState.h"

class TellBuilding : public HandshakingState {
public:
	TellBuilding(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
};