#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class GameError : public CatanState {
public:
	GameError(CatanGame& game) : CatanState(game, CatanGame::State::GAME_ERROR) {}
	void handle(CatanEvent* event);
};