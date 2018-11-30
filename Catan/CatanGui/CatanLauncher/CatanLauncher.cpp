#include "CatanLauncher.h"

CatanLauncher::
CatanLauncher() {
	this->state = States::MAIN_MENU;
}

void
CatanLauncher::run() {

	/*
	* Se ejecuta segun el estado
	*/
	switch ( state ) {

		case MAIN_MENU:
			break;

		case CONNECT_MENU:
			break;

		case GAME_WINDOW:
			break;

	}
}

bool
CatanLauncher::alive(void) {
	return state != LAUNCHER_CLOSE;
}

void
CatanLauncher::change(States newState) {
	this->state = newState;
}

CatanContext&
CatanLauncher::getContext(void) {
	return context;
}