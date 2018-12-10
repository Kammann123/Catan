#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

class Winner : public CatanState {
public:
	/*
	* Sub-estado o etapas del estado de ganador
	* donde se espera intercambio de jugadores
	*/
	enum WStates : unsigned int {LOSER_REMATCH, WINNER_ANSWER};

	Winner(CatanGame& _game) : CatanState(_game, CatanGame::State::WINNER), state(LOSER_REMATCH) {}
	void handle(CatanEvent* event);
	WStates getState(void);

private:
	WStates state;
};