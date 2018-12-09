#include "OfferAnswer.h"
#include "GameError.h"
#include "Turn.h"

void
OfferAnswer::handle(CatanEvent* event) {

	/*
	* Estado de espera a la respuesta del jugador contrario
	* para recibir si acepta o no la transaccion o intercambio
	* de cartas, con lo cual, solo valido ese evento
	*/
	if (event->getPlayer() == OPONENT_ID(game.getTurn())) {

		if (event->getEvent() == CatanEvent::Events::YES) {

			/*
			* Se acepta la oferta, como ya fue validada en el estado anterior
			* entonces me solamente ejecuto el intercambio y vuelvo al estado de turno,
			* esperando nuevas acciones
			*/
			game.playerExchange(offer.getGiven(), offer.getRecv(), offer.getPlayer());

			game.addNewEvent(event);
			game.changeState(new Turn(game), "Turn - El jugador acepto la oferta.");
			return;

		}
		else if (event->getEvent() == CatanEvent::Events::NO) {

			/*
			* Se rechaza la oferta, con lo cual no debo hacer el intercambio, y vuelvo
			* al estado de turno, a esperar nuevas acciones del jugador.
			*/
			game.addNewEvent(event);
			game.changeState(new Turn(game), "OfferAnswer - El jugador rechazo la oferta.");
			return;
		}
	}

	/*
	* Hubo un error por recibir algun evento o accion invalida
	* y por ello paso a estado de error.
	*/
	game.changeState(new GameError(game), "OfferAnswer - Se esperaba una respuesta YES o NO del jugador contrario.");
}