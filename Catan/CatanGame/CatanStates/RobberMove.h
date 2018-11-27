#pragma once

#include "CatanState.h"
#include "../CatanGame.h"
#include "../../CatanEvents/RobberMoveEvent.h"

class RobberMove : public CatanState {
public:
	RobberMove(CatanGame& _game) : CatanState(_game, CatanGame::State::ROBBER_MOVE) {}
	void handle(CatanEvent* event);
};