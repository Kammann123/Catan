#include "MainMenu.h"
#include "CatanLauncher.h"
#include "../AllegroWidgets/UIBuilder.h"

#define MAINMENU_MUSIC		"CatanGui\\Sounds\\catan.ogg"
#define MAINMENU_BACKGROUND	"CatanGui\\GUIDesigns\\MainMenu\\background.png"

#define MAINMENU_TEXTBOX_IDLE "CatanGui\\GUIDesigns\\MainMenu\\textbox_idle.png"
#define MAINMENU_TEXTBOX_SELECTED "CatanGui\\GUIDesigns\\MainMenu\\textbox_selected.png"

#define MAINMENU_CONNECT_IDLE "CatanGui\\GUIDesigns\\MainMenu\\connect_idle.png"
#define MAINMENU_CONNECT_FOCUS "CatanGui\\GUIDesigns\\MainMenu\\connect_focused.png"
#define MAINMENU_CONNECT_SELECTED "CatanGui\\GUIDesigns\\MainMenu\\connect_selected.png"

#define CONNECT_FOCUS_SOUND "CatanGui\\Sounds\\button_focus.wav"
#define CONNECT_SELECT_SOUND "CatanGui\\Sounds\\press.wav"

MainMenu::
MainMenu(CatanLauncher& _launcher) : WindowUI(1080, 640), launcher(_launcher) {
	/* Creo los componentes */
	UIComponent* nameBox = UIBuilder::createTextBox("name", 26, TextUI::Mode::LETTER);
	UIComponent* ipBox = UIBuilder::createTextBox("ip", 26, TextUI::Mode::EVERYTHING);
	UIComponent* portBox = UIBuilder::createTextBox("port", 25, TextUI::Mode::NUMBER);
	UIComponent* connectButton = UIBuilder::attachSample(UIBuilder::createButton("connect"));

	/* Configuro los botones! */
	VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_CONNECT_IDLE);
	VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_CONNECT_FOCUS);
	VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_CONNECT_SELECTED);
	VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_CONNECT_SELECTED);
	VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_CONNECT_SELECTED);
	VIEW(connectButton, 0)->updateModelValues();

	VIEW(connectButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, CONNECT_SELECT_SOUND);	
	VIEW(connectButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, CONNECT_FOCUS_SOUND);

	/* Configuro los textbox! */
	VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(nameBox, 0)->updateModelValues();

	VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(ipBox, 0)->updateModelValues();

	VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, MAINMENU_TEXTBOX_IDLE);
	VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, MAINMENU_TEXTBOX_IDLE);
	VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, MAINMENU_TEXTBOX_SELECTED);
	VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, MAINMENU_TEXTBOX_SELECTED);
	VIEW(portBox, 0)->updateModelValues();

	/* Agrego componentes */
	this->attachComponent(nameBox);
	this->attachComponent(ipBox);
	this->attachComponent(portBox);
	this->attachComponent(connectButton);

	/* Posicion de componentes */
	MODEL(nameBox, TextUI*)->setPosition(365, 230);
	MODEL(ipBox, TextUI*)->setPosition(365, 300);
	MODEL(portBox, TextUI*)->setPosition(365, 370);
	MODEL(connectButton, MouseUI*)->setPosition(400, 440);

	/* Configuro el background */
	this->setBackground(MAINMENU_BACKGROUND);
	this->setMusic(MAINMENU_MUSIC);
} 