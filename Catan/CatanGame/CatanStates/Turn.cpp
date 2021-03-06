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
	BuildingEvent* building;
	Building* settlement;
	Building* neighbour;
	OfferEvent* offer;
	BankEvent* bank;

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
				building = (BuildingEvent*)event;

				/* Me fijo que tipo de construccion es la que quiere
				* realizar, para lo cual luego, valido posibilidad economica,
				* ubicacion y luego construyo y notifico. 
				*/
				switch (building->getType()) {

					case BuildingType::CITY:
						if (game.hasCityResources(building->getPlayer())) {
							settlement = game.isValidCity(building->getCoords(), building->getPlayer());
							if (settlement) {

								/* Ejecuto acciones construccion y cobro */
								game.buildCity(settlement, building->getCoords(), building->getPlayer());
								game.payCity(building->getPlayer());
								game.addNewEvent(event);

								/* Notifico */
								game.setInfo(game.getPlayer(game.getTurn())->getName() + " ha colocado una ciudad.");
								return;
							}
						}
						break;

					case BuildingType::ROAD:
						if (game.hasRoadResources(building->getPlayer())) {
							neighbour = game.isValidRoad(building->getCoords(), building->getPlayer());
							if (neighbour) {

								/* Ejecuto acciones construccion y cobro */
								game.buildRoad(neighbour, building->getCoords(), building->getPlayer());
								game.payRoad(building->getPlayer());
								game.addNewEvent(event);

								/* Notifico */
								game.setInfo(game.getPlayer(game.getTurn())->getName() + " ha colocado un road.");
								return;
							}
						}
						break;

					case BuildingType::SETTLEMENT:
						if (game.hasSettlementResources(building->getPlayer())) {
							neighbour = game.isValidSettlement(building->getCoords(), building->getPlayer());
							if (neighbour) {

								/* Ejecuto acciones construccion y cobro */
								game.buildSettlement(neighbour, building->getCoords(), building->getPlayer());
								game.paySettlement(building->getPlayer());
								game.addNewEvent(event);

								/* Notifico */
								game.setInfo(game.getPlayer(game.getTurn())->getName() + " ha colocado settlement.");
								return;
							}
						}
						break;
				}
				
				break;

			case CatanEvent::BANK_TRADE:
				bank = (BankEvent*)event;

				/* Verifico que sea una transaccion valida de tipo
				* banco o maritima, luego valido el intercambio, 
				* y en caso de cumplir, lo ejecuto
				*/
				if (bank->isBankTrade()) {
					if (game.isValidBankExchange(bank->getGiven(), bank->getRecv(), bank->getPlayer())) {
						/* Ejecuto la accion de intercambio */
						game.Exchange(bank->getGiven(), bank->getRecv().front(), bank->getPlayer());

						/* Notifico accion */
						game.setInfo(game.getPlayer(game.getTurn())->getName() + " ha intercambiado con el banco.");
						game.addNewEvent(event);
						return;
					}
				}
				else if (bank->isDockTrade()) {
					if (game.isValidDockExchange(bank->getGiven(), bank->getRecv(), bank->getPlayer())) {
						/* Ejecuto la accion de intercambio */
						game.Exchange(bank->getGiven(), bank->getRecv().front(), bank->getPlayer());

						/* Notifico accion */
						game.setInfo(game.getPlayer(game.getTurn())->getName() + " ha intercambiado con un muelle.");
						game.addNewEvent(event);
						return;
					}
				}
				break;

			case CatanEvent::OFFER_TRADE:
				offer = (OfferEvent*)event;

				/*
				* Verifico que la oferta sea valida y posteriormente
				* cambio de estado en caso de serla, a la espera de una respuesta
				*/
				if (game.isValidPlayerExchange(offer->getGiven(), offer->getRecv(), offer->getPlayer())) {

					/* Notifico */
					game.addNewEvent(event);

					/* Cambio de estado a esperar la respuesta del otro jugador */
					game.changeState(new OfferAnswer(game, *offer), game.getPlayer(game.getTurn())->getName() + " ha solicitado hacer un cambio con " + game.getPlayer(OPONENT_ID(game.getTurn()))->getName());
					return;
				}
				break;

			case CatanEvent::PASS:
				/* Ejecuto el cambio de turno, luego paso de estado
				* a esperar sus dices, y finalmente notifico el cambio
				*/
				game.toggleTurn();
				game.addNewEvent(event);
				game.changeState(new ThrowDices(game), "El jugador ha pasado de turno. Ahora le toca a " + game.getPlayer(game.getTurn())->getName());
				return;

				break;

		}
	}

	/*
	* Si no fue manejado el evento, es porque no fue tomado como algo
	* valido, con lo cual, se pasa a estado de error
	*/
	game.changeState(new GameError(game), "Turn - Se produjo un error por accion no valida.");
}