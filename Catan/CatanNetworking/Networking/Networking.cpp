#include "Networking.h"
#include <exception>

Networking::
Networking(NetworkingState* state) {
	this->currState = state;
	this->prevState = nullptr;
	this->status = false;
	this->error = "";
}

Networking::
~Networking() {
	if (this->currState)
		delete this->currState;
	if (this->prevState)
		delete this->prevState;
}

NetworkingState*
Networking::getState(void) {
	return currState;
}

string
Networking::getError(void) {
	return error;
}

bool
Networking::good(void) {
	return status;
}

void
Networking::setError(string msg) {
	this->status = false;
	this->error = msg;
}

void
Networking::setError(const char* msg) {
	this->status = false;
	this->error = msg;
}

void
Networking::verifyStatus(void) const {
	if (!status) {
		throw exception("Networking - verifyStatus - Hubo un error en el estado de Networking, revisar!");
	}
}

void
Networking::changeState(NetworkingState* state) {
	delete prevState;
	prevState = currState;
	currState = state;
}