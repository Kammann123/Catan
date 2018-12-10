#include "Winner.h"
#include "GameError.h"
#include "GameSync.h"
#include "GameEnd.h"

void
Winner::handle(CatanEvent* event) {

	/*
	* Valido los eventos recibidos, que pueden ser de tipo
	* PLAY_AGAIN o GAME_OVER, y luego verifico, segun en que estado
	* se encuentra el Winner, si vuelve a jugar o termina aca
	*/
	if (event->getEvent() == CatanEvent::Events::PLAY_AGAIN || event->getEvent() == CatanEvent::Events::GAME_OVER) {

		switch (state) {
			/*
			* En el estado de LOSER_REMATCH espero la decision del perdedor
			* verificando que el evento sea del mismo, y luego si quiere jugar devuelta
			* vamos a WINNER_ANSWER, o en caso de no, terminamos en GAME_END
			*/
			case LOSER_REMATCH:
				if (event->getPlayer() != game.getWinner()) {
					if (event->getEvent() == CatanEvent::Events::PLAY_AGAIN) {
						/* Cambio de estado a WINNER_ANSWER y notifico lo respondido */
						state = WINNER_ANSWER;
						game.addNewEvent(event);
						game.setInfo( game.getPlayer(OPONENT_ID(game.getWinner()))->getName() + " desea jugar una revancha!");
						game.notifyChange();
						return;
					}
					else if (event->getEvent() == CatanEvent::Events::GAME_OVER) {
						/* Cambio de estado a GAME_END, el juego termina y lo notifico */
						game.addNewEvent(event);
						game.changeState(new GameEnd(game), game.getPlayer(OPONENT_ID(game.getWinner()))->getName() + " no desea jugar una revancha.");
						return;
					}
				}
				break;

			/*
			* En el estado WINNER_ANSWER espero la decision del jugador ganador
			* verificando que sea el quien responde con una accion, y luego decido
			* si el juego vuelve a comenzar, o finaliza.
			*/
			case WINNER_ANSWER:
				if (event->getPlayer() == game.getWinner()) {
					if (event->getEvent() == CatanEvent::Events::PLAY_AGAIN) {
						/* Cambio de estado a GAME_SYNC y notifico lo respondido */
						game.changeState(new GameSync(game), game.getPlayer(game.getWinner())->getName() + " acepta jugar una revancha!");
						game.addNewEvent(event);
						return;
					}
					else if (event->getEvent() == CatanEvent::Events::GAME_OVER) {
						/* Cambio de estado a GAME_END, el juego termina y lo notifico */
						game.addNewEvent(event);
						game.changeState(new GameEnd(game), game.getPlayer(game.getWinner())->getName() + " no desea jugar una revancha.");
						return;
					}
				}
				break;
		}
	}

	/*
	* El evento no pudo ser manejado, con lo cual, termino con estado de error
	* y luego notifico con un mensaje.
	*/
	game.changeState(new GameError(game), "Winner - Se esperaba PLAY_AGAIN o GAME_OVER.");
}