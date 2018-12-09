#include "RobberMove.h"
#include "GameError.h"
#include "Turn.h"

void
RobberMove::handle(CatanEvent* event) {

	/*
	* En este estado, se espera del jugador correspondiente al turno,
	* la accion de mover el Robber, con lo cual se valida que llegue ese evento
	* y posteriormente veo 
	*/
	if (event->getEvent() == CatanEvent::Events::ROBBER_MOVE) {
		RobberMoveEvent* robberMove = (RobberMoveEvent*)event;

		if (robberMove->getPlayer() == game.getTurn()) {
			if (game.validRobberMovement(robberMove->getCoord())) {

				/* Ejecuto la accion de mover el robber */
				game.moveRobber(robberMove->getCoord());

				/* Notifico el evento */
				game.addNewEvent(event);

				/* Cambio de estado */
				game.changeState(new Turn(game), "RobberMove - Robber movido correctamente!");

				return;
			}
		}

		/*
		* Error por accion invalida, ya sea su validacion como su autorizacion
		*/
		game.changeState(new GameError(game), "RobberMove - Accion ROBBER_MOVE invalida.");
	}
	else {

		/*
		* Evento recibido invalido para el estado actual, se procede
		* a salir del juego con error
		*/
		game.changeState(new GameError(game), "RobberMove - Se esperaba accion ROBBER_MOVE.");
	}
}