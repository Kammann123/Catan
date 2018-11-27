#pragma once

#include "CatanState.h"
#include "../CatanGame.h"
#include "../../CatanEvents/OfferEvent.h"

class OfferAnswer : public CatanState {
public:
	OfferAnswer(CatanGame& _game, OfferEvent _offer) : CatanState(_game, CatanGame::State::OFFER_ANSWER), offer(_offer) {}
	void handle(CatanEvent* event);
private:
	OfferEvent offer;
};