#include "Turn.h"
#include "GameError.h"
#include "ThrowDices.h"
#include "../../CatanEvents/BuildingEvent.h"

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

						break;

					case BuildingType::ROAD:
						break;

					case BuildingType::SETTLEMENT:
						break;
				}
				
				break;

			case CatanEvent::BANK_TRADE:
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