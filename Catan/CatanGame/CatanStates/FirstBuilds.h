#pragma once

#include "CatanState.h"
#include "../CatanGame.h"

#define MAX_BUILD_STAGE	4

class FirstBuilds : public CatanState {
public:

	/*
	* Estados de la etapa FirstBuilds, es la alternacion entre
	* la colocacion de un settlement y la colocacion de un road,
	* alternando segun es debido, los jugadores que corresponden
	*/
	enum FBStates : unsigned int { BUILD_SETTLEMENT, BUILD_ROAD };
	const bool toggleTurn[MAX_BUILD_STAGE] = { false, true, false, true };

	FirstBuilds(CatanGame& game);
	void handle(CatanEvent* event);
	unsigned int getState(void);

private:
	FBStates state;
	unsigned int stage;
};