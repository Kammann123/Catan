#include "FirstBuilds.h"
#include "GameError.h"
#include "ThrowDices.h"

#include "../../CatanEvents/BuildingEvent.h"

FirstBuilds::
FirstBuilds(CatanGame& game) : CatanState(game, CatanGame::State::FIRST_BUILDS) {
	state = FBStates::BUILD_SETTLEMENT;
	stage = 0;
}

void
FirstBuilds::handle(CatanEvent* event) {

	/*
	* En casa entrada verifico que estado estoy, si espero una construccion de
	* un asentamiento o si espero un camino, y valido que el jugador sea el 
	* correspondiente.
	*/
	switch (state) {

		case BUILD_SETTLEMENT:

			/* Valido que haya llegado una construccion settlement */
			if (event->getEvent() == CatanEvent::Events::BUILDING) {
				BuildingEvent* building = (BuildingEvent*)event;
				if (building->getType() == BuildingType::SETTLEMENT) {

					/*
					* Valido que la construccion sea del jugador correspondiente,
					* y que ademas cumpla las reglas de construccion
					*/
					if (building->getPlayer() == game.getTurn()) {
						if (game.validFirstSettlement(building->getCoords(), building->getPlayer())) {

							/* Realizo la construccion */
							game.buildSettlement(nullptr, building->getCoords(), building->getPlayer());

							/* Asigno recursos en la segunda vuelta */
							if (stage > 1) {
								game.assignResources(building->getType(), building->getCoords(), building->getPlayer());
							}

							/* Guardo el evento de construccion */
							game.addNewEvent(event);

							/* Cambio de estado interno */
							state = FBStates::BUILD_ROAD;
							return;
						}
					}
					game.changeState(new GameError(game), "FirstBuilds - Peticion de construccion de SETTLEMENT no cumple validacion.");
				}
				else {
					game.changeState(new GameError(game), "FirstBuilds - Construccion invalida, se esperaba settlement.");
				}
			}
			else {
				game.changeState(new GameError(game), "FirstBuilds - Se esperaba una construccion. Accion invalida.");
			}
			break;

		case BUILD_ROAD:

			/* Valido que haya llegado una construccion settlement */
			if (event->getEvent() == CatanEvent::Events::BUILDING) {
				BuildingEvent* building = (BuildingEvent*)event;
				if (building->getType() == BuildingType::ROAD) {

					/*
					* Valido que la construccion sea del jugador correspondiente,
					* y que ademas cumpla las reglas de construccion
					*/
					if (building->getPlayer() == game.getTurn()) {
						Building* neighbour = game.isValidRoad(building->getCoords(), building->getPlayer());
						if (neighbour) {

							/* Realizo la construccion */
							game.buildRoad(neighbour, building->getCoords(), building->getPlayer());

							/* Guardo el evento de construccion */
							game.addNewEvent(event);

							/* Cambio de estado interno */
							state = FBStates::BUILD_SETTLEMENT;
							stage++;
							if (stage == MAX_BUILD_STAGE) {
								game.changeState(new ThrowDices(game), "FirstBuilds - Construcciones iniciales realizadas! Comienza el primer turno.");
							}
							else {
								/* Verifico alternancia de turno */
								if (toggleTurn[stage])	game.toggleTurn();
							}
							return;
						}
					}
					game.changeState(new GameError(game), "FirstBuilds - Peticion de construccion de ROAD no cumple validacion.");
				}
				else {
					game.changeState(new GameError(game), "FirstBuilds - Construccion invalida, se esperaba road.");
				}
			}
			else {
				game.changeState(new GameError(game), "FirstBuilds - Se esperaba una construccion. Accion invalida.");
			}
			break;
	}
}

unsigned int
FirstBuilds::getState(void) {
	return state;
}