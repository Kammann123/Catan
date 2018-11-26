#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class FirstBuilds : public CatanState {
public:
	FirstBuilds(CatanGame& game) : CatanState(game, CatanGame::State::FIRST_BUILDS) {}
	void handle(CatanEvent* event);
};