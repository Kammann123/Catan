#pragma once

#include "../../CatanEvents/SyncEvent.h"

#include "CatanState.h"
#include "../CatanGame.h"

class GameSync : public CatanState {
public:
	GameSync(CatanGame& game) : CatanState(game, CatanGame::State::GAME_SYNC) {}
	void handle(CatanEvent* event);
};