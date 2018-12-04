#include "GameWindow.h"
#include "../CatanLauncher.h"

#define GAMEWINDOW_BACKGROUND ""

GameWindow::
GameWindow(CatanLauncher& _launcher) : launcher(_launcher), WindowUI(1080, 640) {

	/* Configuro los aspectos generales de la ventana */
	this->setBackground()
}