#pragma once

#include "HandshakingState.h"

class TellQuit : public HandshakingState {
public:
	TellQuit(CatanNetworking& net);
};