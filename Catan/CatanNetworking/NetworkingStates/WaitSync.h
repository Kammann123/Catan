#pragma once

#include "HandshakingState.h"
#include "../../CatanEvents/SyncEvent.h"

class WaitSync : public HandshakingState {
public:
	WaitSync(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	NetworkPacket * getLocalName(void);
	void setRemoteName(NetworkPacket* packet);
	void setMap(NetworkPacket* packet);
	void setTokens(NetworkPacket* packet);
	void setTurn(NetworkPacket* packet);
	bool doIStart(void);
	void createEvent(NetworkPacket* packet);

	SyncEvent* event;
};