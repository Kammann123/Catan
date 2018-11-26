#include "GameSync.h"
#include "GameError.h"
#include "FirstBuilds.h"

void
GameSync::handle(CatanEvent* event) {

	/*
	* En la etapa de sincronizacion del juego entre miembros
	* de la partida, existen dos eventos que son validos, ASK_SYNC,
	* y SYNC, uno establece peticion de generacion del entorno del juego
	* y el otro entrega la informacion del mismo. Cualquier otra cosa es error.
	*/
	if (event->getEvent() == CatanEvent::Events::ASK_SYNC) {

		/* Ejecuto rutinas de generacion del entorno de juego */
		game.generateMap();
		game.generateOcean();
		game.generateTokens();
		game.generateTurn();

		/* Paso a nuevo estado de primeras construcciones */
		game.setInfo("GameSync - Se genero el entorno del juego correctamente!");
		game.changeState(new FirstBuilds(game));
	}
	else if (event->getEvent() == CatanEvent::Events::SYNC) {

		/* Extraigo del evento informacion de configuracion */
		SyncEvent* sync = (SyncEvent*)event;
		NameData remoteName = sync->getRemoteName();
		MapData map = sync->getMap();
		TokenData tokens = sync->getTokens();
		PlayerId turn = sync->getTurn();

		/*
		* Valido que las configuraciones sean correctas
		*/
		if (turn == PlayerId::PLAYER_ONE || turn == PlayerId::PLAYER_TWO) {

			if (game.verifyMap(map.getMap()) && game.verifyTokens(tokens.getTokens())) {

				/* Ejecuto las rutinas de configuracion del entorno
				* a partir de los paquetes recibidos como evento
				*/
				game.setRemoteName(remoteName.getName());
				game.setGlobalMap(map.getMap(), tokens.getTokens());
				game.setTurn(turn);

				/* Paso a nuevo estado de primeras construcciones */
				game.setInfo("GameSync - Sincronizacion recibida exitosamente!");
				game.changeState(new FirstBuilds(game));
			}
		}

		/*
		* Se genero un error, por lo cual se debe pasar a dicho estado
		* y comunicar un mensaje apropiado
		*/
		game.setInfo("GameSync - La informacion recibida de sincronizacion era invalida.");
		game.changeState(new GameError(game));
	}
	else {

		/*
		* Ante la aparicion de un error, guardo un mensaje de error y paso el
		* catan a un estado de error, con un mensaje descriptivo 
		*/
		game.setInfo("GameSync - Hubo un error en la secuencia del juego, se esperaba sincronizacion.");
		game.changeState(new GameError(game));
	}
}