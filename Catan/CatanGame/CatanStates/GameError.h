#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class GameError : public CatanState {
public:
	GameError(CatanGame& game);
	void handle(CatanEvent* event);
};