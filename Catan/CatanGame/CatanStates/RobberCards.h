#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class RobberCards : public CatanState {
public:
	RobberCards(CatanGame& _game, PlayerId _player) : CatanState(_game, CatanGame::State::ROBBER_CARD), player(_player) {}
	void handle(CatanEvent* event);
	PlayerId getPlayerId(void);
private:
	PlayerId player;
};