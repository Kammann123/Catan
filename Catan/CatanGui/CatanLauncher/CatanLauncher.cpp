#include "CatanLauncher.h"

CatanLauncher::
CatanLauncher() : mainmenu(*this), gamewindow(*this) {
	this->state = States::GAME_WINDOW;
}

void
CatanLauncher::run() {
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