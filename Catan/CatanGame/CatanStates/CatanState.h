#pragma once

#include "../../CatanEvents/CatanEvent.h"

class CatanGame;

/*
* CatanState
* Estado del juego catan, para el uso en el patron de diseño
* State, cambiando el comportamiento de CatanGame, como context.
*/
class CatanState {
public:

	/* Constructor */
	CatanState(CatanGame& _game, unsigned int _id) : game(_game), id(_id) {}

	/*
	* handle
	* Maneja un evento del Catan para poder realizar alguna
	* accion en el mismo.
	*/
	virtual void handle(CatanEvent* event) = 0;

	virtual unsigned int getState(void) { return 0; }

	/*
	* getId
	* Devuelve la definicion del estado de la implementacion, es basicamente
	* lo que identifica a cada uno de los estados mas grandes
	*/
	unsigned int getId(void) { return id; }

protected:
	const unsigned int id;
	CatanGame & game;
};