#pragma once

#include "HandshakingState.h"

class TellBank : public HandshakingState {
public:
	TellBank(CatanNetworking& net);
};