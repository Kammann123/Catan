#pragma once

#include "HandshakingState.h"

class ListenQuit : public HandshakingState {
public:
	ListenQuit(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void setQuit(NetworkPacket* packet);
};