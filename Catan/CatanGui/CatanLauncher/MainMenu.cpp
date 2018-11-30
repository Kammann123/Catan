#include "MainMenu.h"

#include "CatanLauncher.h"

#define MAINMENU_BACKGROUND	"CatanGui\\GUIDesigns\\MainMenu\\background.png"

MainMenu::
MainMenu(CatanLauncher& _launcher) : WindowUI(1080, 640), launcher(_launcher){

	/* Configuro el background */
	this->setBackground(MAINMENU_BACKGROUND);
}