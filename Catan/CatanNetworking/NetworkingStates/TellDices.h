#pragma once

#include "HandshakingState.h"

class TellDices : public HandshakingState {
public:
	TellDices(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	bool isRobber(void);
	void remoteRobberCards(NetworkPacket* packet);
};