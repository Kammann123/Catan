#include "GameWindow.h"

#include "../../AllegroWidgets/UIBuilder.h"
#include "../CatanLauncher.h"

#define GAMEWINDOW_BACKGROUND "CatanGui\\GUIDesigns\\GameMenu\\background.png"

#define GAMEWINDOW_EXIT_NORMAL "CatanGui\\GUIDesigns\\GameMenu\\exit_normal.png"
#define GAMEWINDOW_EXIT_FOCUSED "CatanGui\\GUIDesigns\\GameMenu\\exit_focused.png"
#define GAMEWINDOW_EXIT_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\exit_selected.png"

#define GAMEWINDOW_DISCARD_NORMAL "CatanGui\\GUIDesigns\\GameMenu\\discard_normal.png"
#define GAMEWINDOW_DISCARD_FOCUSED "CatanGui\\GUIDesigns\\GameMenu\\discard_focused.png"
#define GAMEWINDOW_DISCARD_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\discard_selected.png"

#define GAMEWINDOW_TRADE_NORMAL "CatanGui\\GUIDesigns\\GameMenu\\trade_normal.png"
#define GAMEWINDOW_TRADE_FOCUSED "CatanGui\\GUIDesigns\\GameMenu\\trade_focused.png"
#define GAMEWINDOW_TRADE_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\trade_selected.png"


GameWindow::
GameWindow(CatanLauncher& _launcher) : launcher(_launcher), WindowUI(1080, 640) {
	UIComponent* exitButton = UIBuilder::createButton("exit");
	UIComponent* discardButton = UIBuilder::createButton("discard");
	UIComponent* tradeButton = UIBuilder::createButton("trade");

	/****************************/
	/* Configuracion de botones */
	/****************************/
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_EXIT_NORMAL);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_EXIT_FOCUSED);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_EXIT_SELECTED);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_EXIT_SELECTED);
	VIEW(exitButton, 0)->updateModelValues();

	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_DISCARD_NORMAL);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_DISCARD_FOCUSED);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_DISCARD_SELECTED);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_DISCARD_SELECTED);
	VIEW(discardButton, 0)->updateModelValues();

	VIEW(tradeButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_TRADE_NORMAL);
	VIEW(tradeButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_TRADE_FOCUSED);
	VIEW(tradeButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_TRADE_SELECTED);
	VIEW(tradeButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_TRADE_SELECTED);
	VIEW(tradeButton, 0)->updateModelValues();

	/***********************************
	* Agrego componente a la interfaz  *
	***********************************/
	this->attachComponent(exitButton);
	this->attachComponent(discardButton);
	this->attachComponent(tradeButton);

	/**************************************
	* Configuro posiciones de la interfaz *
	**************************************/
	MODEL(exitButton, MouseUI*)->setPosition(63, 240);
	MODEL(discardButton, MouseUI*)->setPosition(63, 190);
	MODEL(tradeButton, MouseUI*)->setPosition(63, 140);

	/***********************************
	* Configuro general de la interfaz *
	***********************************/
	this->setBackground(GAMEWINDOW_BACKGROUND);

	/**************************
	* Activo el layout actual *
	**************************/
	normal_layout();
}

void
GameWindow::normal_layout(void) {

	/************************
	* Configuro los botones *
	************************/
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["exit"]->getModel()->setVisible(true);

	(*this)["discard"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setVisible(true);

	(*this)["trade"]->getModel()->setEnable(true);
	(*this)["trade"]->getModel()->setVisible(true);

}