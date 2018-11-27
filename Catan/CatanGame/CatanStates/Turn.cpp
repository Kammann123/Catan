#include "Turn.h"
#include "GameError.h"
#include "Winner.h"
#include "ThrowDices.h"
#include "OfferAnswer.h"

#include "../../CatanEvents/BuildingEvent.h"
#include "../../CatanEvents/OfferEvent.h"
#include "../../CatanEvents/BankEvent.h"

void
Turn::handle(CatanEvent* event) {

	/*
	* En este estado se aceptan diferentes acciones que el jugador
	* en turno puede ir realizando, como por ejemplo, realizar un cambio
	* de cartas con el banco, con el muelle, con el usuario ( en cuyo caso
	* debera esperar una respuesta en otro estado ) y luego construir cosas.
	*
	* Posteriormente, podria agregar algo para cartas de desarrollo
	*/

	if (event->getPlayer() == game.getTurn()) {

		switch (event->getEvent()) {

			case CatanEvent::Events::BUILDING:
				BuildingEvent * building = (BuildingEvent*)event;

				/* Me fijo que tipo de construccion es la que quiere
				* realizar, para lo cual luego, valido posibilidad economica,
				* ubicacion y luego construyo y notifico. 
				*/
				switch (building->getType()) {

					case BuildingType::CITY:
						if (game.hasCityResources(building->getPlayer())) {
							Building* settlement = game.isValidCity(building->getCoords(), building->getPlayer());
							if (settlement) {

								/* Ejecuto acciones construccion y cobro */
								game.buildCity(settlement, building->getCoords(), building->getPlayer());
								game.payCity(building->getPlayer());
								game.addNewEvent(event);

								/* Verifico si gano... */
								if (game.hasWinner()) {
									/* Mando el evento de ganador/perdedor */
									CatanEvent::Events endingEvent = PlayerId::PLAYER_ONE == game.getWinner() ? CatanEvent::Events::WON : CatanEvent::Events::LOST;
									game.addNewEvent(new CatanEvent(endingEvent, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_ONE));

									/* Cambio de estado a ganador */
									game.changeState(new Winner(game), "Turn - Un jugador ha ganado la partida!");
								}
								else {

									/* Notifico */
									game.setInfo("Turn - El jugador ha colocado ciudad correctamente!");
								}
								return;
							}
						}
						break;

					case BuildingType::ROAD:
						if (game.hasRoadResources(building->getPlayer())) {
							Building* neighbour = game.isValidRoad(building->getCoords(), building->getPlayer());
							if (neighbour) {

								/* Ejecuto acciones construccion y cobro */
								game.buildRoad(neighbour, building->getCoords(), building->getPlayer());
								game.payRoad(building->getPlayer());
								game.addNewEvent(event);

								/* Verifico si gano... */
								if (game.hasWinner()) {
									/* Mando el evento de ganador/perdedor */
									CatanEvent::Events endingEvent = PlayerId::PLAYER_ONE == game.getWinner() ? CatanEvent::Events::WON : CatanEvent::Events::LOST;
									game.addNewEvent(new CatanEvent(endingEvent, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_ONE));

									/* Cambio de estado a ganador */
									game.changeState(new Winner(game), "Turn - Un jugador ha ganado la partida!");
								}
								else {

									/* Notifico */
									game.setInfo("Turn - El jugador ha colocado road correctamente!");
								}
								return;
							}
						}
						break;

					case BuildingType::SETTLEMENT:
						if (game.hasSettlementResources(building->getPlayer())) {
							Building* neighbour = game.isValidCity(building->getCoords(), building->getPlayer());
							if (neighbour) {

								/* Ejecuto acciones construccion y cobro */
								game.buildSettlement(neighbour, building->getCoords(), building->getPlayer());
								game.paySettlement(building->getPlayer());
								game.addNewEvent(event);

								/* Verifico si gano... */
								if (game.hasWinner()) {
									/* Mando el evento de ganador/perdedor */
									CatanEvent::Events endingEvent = PlayerId::PLAYER_ONE == game.getWinner() ? CatanEvent::Events::WON : CatanEvent::Events::LOST;
									game.addNewEvent(new CatanEvent(endingEvent, CatanEvent::Sources::NETWORKING, PlayerId::PLAYER_ONE));

									/* Cambio de estado a ganador */
									game.changeState(new Winner(game), "Turn - Un jugador ha ganado la partida!");
								}
								else {

									/* Notifico */
									game.setInfo("Turn - El jugador ha colocado settlement correctamente!");
								}
								return;
							}
						}
						break;
				}
				
				break;

			case CatanEvent::BANK_TRADE:
				BankEvent * bank = (BankEvent*)event;

				/* Verifico que sea una transaccion valida de tipo
				* banco o maritima, luego valido el intercambio, 
				* y en caso de cumplir, lo ejecuto
				*/
				if (bank->isBankTrade()) {
					bool valid = false;

					if (bank->hasLocal()) {
						valid = game.isValidBankExchange(bank->getGivenCards(), bank->getPlayer());
					}
					else {
						valid = game.isValidBankExchange(bank->getGiven(), bank->getPlayer());
					}

					if (valid) {
						/* Ejecuto la accion de intercambio */
						if (bank->hasLocal()) {
							game.Exchange( bank->getGivenCards(), bank->getRecv().front(), bank->getPlayer() );
						}
						else {
							game.Exchange( bank->getGiven(), bank->getRecv().front(), bank->getPlayer() );
						}

						/* Notifico accion */
						game.setInfo("Turn - Intercambio con el banco realizado correctamente!");
						game.addNewEvent(event);
						return;
					}
				}
				else if (bank->isDockTrade()) {
					bool valid = false;

					if (bank->hasLocal()) {
						valid = game.isValidDockExchange(bank->getGivenCards(), bank->getPlayer());
					}
					else {
						valid = game.isValidDockExchange(bank->getGiven(), bank->getPlayer());
					}

					if (valid) {
						/* Ejecuto la accion de intercambio */
						if (bank->hasLocal()) {
							game.Exchange(bank->getGivenCards(), bank->getRecv().front(), bank->getPlayer());
						}
						else {
							game.Exchange(bank->getGiven(), bank->getRecv().front(), bank->getPlayer());
						}

						/* Notifico accion */
						game.setInfo("Turn - Intercambio con puerto realizado correctamente!");
						game.addNewEvent(event);
						return;
					}
				}
				break;

			case CatanEvent::OFFER_TRADE:
				OfferEvent * offer = (OfferEvent*)event;

				/*
				* Verifico que la oferta sea valida y posteriormente
				* cambio de estado en caso de serla, a la espera de una respuesta
				*/
				bool valid = false;

				if (offer->hasLocal()) {
					valid = game.isValidPlayerExchange(offer->getGivenCards(), offer->getRecv(), offer->getPlayer());
				}
				else {
					valid = game.isValidPlayerExchange(offer->getGiven(), offer->getRecv(), offer->getPlayer());
				}

				if (valid) {
					/* Cambio de estado a esperar la respuesta del otro jugador */
					game.changeState(new OfferAnswer(game, *offer), "Turn - Oferta de intercambio ok! Esperando respuesta...");

					/* Notifico */
					game.addNewEvent(event);
					return;
				}
				break;

			case CatanEvent::PASS:
				/* Ejecuto el cambio de turno, luego paso de estado
				* a esperar sus dices, y finalmente notifico el cambio
				*/
				game.toggleTurn();
				game.changeState(new ThrowDices(game), "Turn - Cambio de turno!");
				game.addNewEvent(event);
				break;

		}
	}

	/*
	* Si no fue manejado el evento, es porque no fue tomado como algo
	* valido, con lo cual, se pasa a estado de error
	*/
	game.changeState(new GameError(game), "Turn - Se produjo un error por accion no valida.");
}