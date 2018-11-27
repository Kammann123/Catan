#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class GameEnd : public CatanState {
public:
	GameEnd(CatanGame& _game) : CatanState(_game, CatanGame::State::GAME_END) {}
	void handle(CatanEvent* event);
};