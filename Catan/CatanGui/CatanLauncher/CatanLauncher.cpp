#include "CatanLauncher.h"

CatanLauncher::
CatanLauncher() : mainmenu(*this), gamewindow(*this) {
	this->state = States::GAME_WINDOW;
}

void
CatanLauncher::run() {

	/* Se corren los estados del launcher
	*/
	switch ( state ) {
		case MAIN_MENU:
			if (!mainmenu.isOpen()) {
				mainmenu.start();
			}
			else {
				mainmenu.run();
			}
			break;

		case GAME_WINDOW:
			if (!gamewindow.isOpen()) {
				gamewindow.start();
			}
			else {
				gamewindow.run();
			}
			break;
	}

	/* Me fijo si el modo o estado actual del networking esta
	* en funcionamiento, para correr sus procesos... y luego verificar su estado!
	*/
	if (state != CatanNetworking::States::CLOSED &&
		state != CatanNetworking::States::IDLE &&
		state != CatanNetworking::States::NET_ERROR) {
		CatanNetworking& net = getContext().getNetworking();

		/* Verifico en que estado se encuentra el networking, y en caso de
		* fallar, deberia indicar el error, volver al estado closed!
		*/
		if (net.good()) {
			net.run();
		}
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