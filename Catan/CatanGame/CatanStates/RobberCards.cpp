#include "RobberCards.h"
#include "GameError.h"
#include "../../CatanEvents/RobberCardEvent.h"

void
RobberCards::handle(CatanEvent* event) {

	/*
	* Este estado se construye siempre guardando el id
	* del jugador del cual se espera que robe cartas,
	* de esa forma, se reutiliza la misma logica de estado
	* tomando como id alguno distinto.
	*
	* Primero se valida recibir RobberCardsEvent, y luego
	* que sea del jugador esperado 
	*/
	if (event->getEvent() == CatanEvent::Events::ROBBER_CARDS) {
		RobberCardEvent* robberCards = (RobberCardEvent*)event;

		if (robberCards->getPlayer() == player) {

			if () {

			}
		}

		/*
		* No cumple la validacion o requisitos para la accion
		* estado de error!
		*/
		game.changeState(new GameError(game), "RobberCards - La accion robber cards fue invalida.");
	}
	else {

		/*
		* Accion invalida o mensaje incorrecto, se manda
		* a estado de error el juego
		*/
		game.changeState(new GameError(game), "RobberCards - Se esperaba accion ROBBER_CARDS.");
	}
}