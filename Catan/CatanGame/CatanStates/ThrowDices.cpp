#include "ThrowDices.h"
#include "GameError.h"
#include "RobberCards.h"
#include "RobberMove.h"

void
ThrowDices::handle(CatanEvent* event) {

	/*
	* En este estado se esta a la espera de que se 
	* arrojen los dados, con lo cual unicamente es valido recibir
	* del player en turno, un evento de tirar los dados, 
	* con lo cual se verifica recepcion de dicho evento
	*/
	if (event->getEvent() == CatanEvent::Events::THROW_DICES) {
		DicesEvent* dices = (DicesEvent*)event;

		/*
		* Verifico que la accion sea del jugador correcto y luego
		* que los valores de dados sean validados
		*/
		if (dices->getPlayer() == game.getTurn()) {
			if (game.validDices(dices->getDices())) {

				/*
				* Verifico si la jugada es correspondiente a activar
				* el modo Robber o no, en caso de no serlo, se asignan recursos
				* y en caso de si, se llama al RobberCards
				*/
				if (game.isRobberDices(dices->getDices())) {

					if ( game.hasRobberCards(OPONENT_ID(game.getTurn())) ) {
						game.changeState(new RobberCards(game, game.getTurn()), "ThrowDices - El primer jugador debe descartar cartas!");
					}
					else {
						if (game.hasRobberCards(game.getTurn())) {
							game.changeState(new RobberCards(game, game.getTurn()), "ThrowDices - El segundo jugador debe descartar cartas!");
						}
						else {
							game.changeState(new RobberMove(game), "ThrowDices - Nadie debe descartar cartas.");
						}
					}
				}
				else {

					/*
					* Asigno los recursos y cambio de estado esperando acciones
					* del turo del jugador
					*/
					game.assignResources(dices->getDices());
					// -----> CAMBIO DE ESTADO A TURN <-------
				}

				/* Notifico la accion a los observers */
				game.addNewEvent(event);

				return;
			}
		}

		/*
		* Hubo algun tipo de error en la validacion, por el turno o los dados
		* cambio de estado y lo notifico
		*/
		game.changeState(new GameError(game), "ThrowDices - Fallo la validacion de los dados o el jugador.");
	}
	else {

		/*
		* Recibi un mensaje o accion que no deberia ser valido
		* pues se esta esperando que se ejecute un tirar dados
		*/
		game.changeState(new GameError(game), "ThrowDices - Se esperaba recibir una jugada de dados.");
	}
}