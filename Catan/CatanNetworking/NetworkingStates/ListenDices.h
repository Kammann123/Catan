#pragma once

#include "HandshakingState.h"

class ListenDices : public HandshakingState {
public:
	ListenDices(CatanNetworking& net);
private:
	unsigned int decideRobber(void);
	void setDices(NetworkPacket* packet);
	void setRemoteCards(NetworkPacket* packet);
	void setRobberMove(NetworkPacket* packet);
};