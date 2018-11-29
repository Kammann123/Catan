#pragma once

#include "HandshakingState.h"

class TellDices : public HandshakingState {
public:
	TellDices(CatanNetworking& net);
private:
	bool isRobber(void);
	void remoteRobberCards(NetworkPacket* packet);
	void pass(NetworkPacket* packet);
};