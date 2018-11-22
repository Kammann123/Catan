#include "CatanStatus.h"

CatanStatus::
CatanStatus(State state, string error) {
	this->state = state;
	this->error = error;
}

CatanStatus::
CatanStatus(State state) {
	this->state = state;
	this->error = "";
}

CatanStatus::
CatanStatus(void) {
	this->state = State::OK;
	this->error = "";
}

CatanStatus::State 
CatanStatus::getState(void) const {
	return this->state;
}

string
CatanStatus::getError(void) const {
	return this->error;
}