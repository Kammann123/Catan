#pragma once

#include "HandshakingState.h"

class Sync : public HandshakingState {
public:
	Sync(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void setRemoteName(NetworkPacket* packet);
	NetworkPacket* getLocalName(void);
	NetworkPacket* getMap(void);
	NetworkPacket* getTokens(void);
	bool whoStarts(void);
};