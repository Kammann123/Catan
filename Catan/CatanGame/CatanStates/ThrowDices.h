#pragma once

#include "CatanState.h"
#include "../CatanGame.h"
#include "../../CatanEvents/DicesEvent.h"

class ThrowDices : public CatanState {
public:
	ThrowDices(CatanGame& game) : CatanState(game, CatanGame::State::THROW_DICES) {}
	void handle(CatanEvent* event);
};