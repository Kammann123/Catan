#pragma once

#include "HandshakingState.h"
#include "../../CatanEvents/SyncEvent.h"

class ListenEnd : public HandshakingState {
public:
	ListenEnd(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void userWon(NetworkPacket* packet);
	void gameOver(NetworkPacket* packet);
	void playAgain(NetworkPacket* packet);
	void setMap(NetworkPacket* packet);
	void setTokens(NetworkPacket* packet);
	void setTurn(NetworkPacket* packet);
	void createEvent(NetworkPacket* packet);
	bool doIStart(void);

	SyncEvent* event;
};