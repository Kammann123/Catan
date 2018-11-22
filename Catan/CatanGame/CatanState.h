#pragma once

class CatanGame;

/*
* CatanState
* Estado del juego catan, para el uso en el patron de diseño
* State, cambiando el comportamiento de CatanGame, como context.
*/
class CatanState {
public:

	using Type = unsigned int;

	/* Constructor */
	CatanState(CatanGame& _game) : game(_game) {}

	/*
	* handle
	* Maneja un evento del Catan para poder realizar alguna
	* accion en el mismo.
	*/
	virtual CatanStatus handle(CatanEvent* event) = 0;

	/*
	* getType
	* Devuelve el tipo de estado que tiene la implementacion
	*/
	virtual Type getType(void) const = 0;

private:

	CatanGame & game;
};