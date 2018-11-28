#pragma once

#include "HandshakingState.h"

class ListenQuit : public HandshakingState {
public:
	ListenQuit(CatanNetworking& net);
private:
	void setQuit(NetworkPacket* packet);
};