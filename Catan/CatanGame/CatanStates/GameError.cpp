#include "GameError.h"

#include "../../CatanEvents/CatanEvent.h"

GameError::
GameError(CatanGame& game) : CatanState(game, CatanGame::State::GAME_ERROR) {

	/*
	* Se crea un evento de tipo error y luego en ese mismo lugar
	* se notifica a los observers de un cambio de estado del juego
	*/
	game.addNewEvent(new CatanEvent(CatanEvent::Events::ERROR_EVENT, CatanEvent::Sources::GAME, PlayerId::PLAYER_NONE));
}

void
GameError::handle(CatanEvent* event) {}