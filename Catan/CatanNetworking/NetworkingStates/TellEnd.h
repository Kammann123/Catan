#pragma once

#include "HandshakingState.h"

class TellEnd : public HandshakingState {
public:
	TellEnd(CatanNetworking& net);
	virtual bool isHeader(PacketHeader header);
private:
	void askSync(NetworkPacket* packet);
	void gameOver(NetworkPacket* packet);
	void playAgain(NetworkPacket* packet);
	NetworkPacket* getTokens(void);
	bool whoStarts(void);
};