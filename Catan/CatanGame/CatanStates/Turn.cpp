#include "Turn.h"
#include "GameError.h"
#include "ThrowDices.h"
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

								/* Notifico */
								game.setInfo("Turn - El jugador ha colocado ciudad correctamente!");
								game.addNewEvent(event);
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

								/* Notifico */
								game.setInfo("Turn - El jugador ha colocado road correctamente!");
								game.addNewEvent(event);
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

								/* Notifico */
								game.setInfo("Turn - El jugador ha colocado settlement correctamente!");
								game.addNewEvent(event);
								return;
							}
						}
						break;
				}
				
				break;

			case CatanEvent::BANK_TRADE:
				BankEvent * bank = (BankEvent*)event;


				break;

			case CatanEvent::OFFER_TRADE:
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