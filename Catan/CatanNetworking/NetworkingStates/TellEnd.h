#pragma once

#include "HandshakingState.h"

class TellEnd : public HandshakingState {
public:
	TellEnd(CatanNetworking& net);
private:
	void askSync(NetworkPacket* packet);
	void gameOver(NetworkPacket* packet);
	void playAgain(NetworkPacket* packet);
	NetworkPacket* getTokens(void); 
	NetworkPacket* getMap(void);
	bool whoStarts(void);
};