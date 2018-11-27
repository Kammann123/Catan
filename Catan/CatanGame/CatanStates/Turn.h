#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class Turn : public CatanState {
public:
	Turn(CatanGame& _game) : CatanState(_game, CatanGame::State::TURN) {}
	void handle(CatanEvent* event);
};