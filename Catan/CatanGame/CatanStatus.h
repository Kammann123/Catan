#pragma once

#include <iostream>

using namespace std;

/*
* CatanStatus
* Esatdo actual como respuesta de sucesos en CatanGame
*/
class CatanStatus {
public:

	/* State */
	enum State : unsigned int {OK, ERROR_STATE};

	/* Constructores */
	CatanStatus(State state, string error);
	CatanStatus(State state);
	CatanStatus();

	/*
	* getState
	* Devuelve estado de status
	*/
	State getState(void) const;

	/*
	* getError
	* Devuelve el mensaje de error
	*/
	string getError(void) const;
private:
	string error;
	State state;
};