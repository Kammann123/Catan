#include "GameMenu.h"
#include "CatanLauncher.h"
#include "../AllegroWidgets/UIBuilder.h"

#define GAMEMENU_MUSIC		"CatanGui\\Sounds\\catan.ogg"
#define GAMEMENU_BACKGROUND	"CatanGui\\GUIDesigns\\GameMenu\\background.png"


#define GAMEMENU_DISCARD_ON "CatanGui\\GUIDesigns\\GameMenu\\discard_on.png"
#define GAMEMENU_DISCARD_OFF "CatanGui\\GUIDesigns\\GameMenu\\discard_off.png"

#define GAMEMENU_EXCHANGE_ON "CatanGui\\GUIDesigns\\GameMenu\\exchange_on.png"
#define GAMEMENU_EXCHANGE_OFF "CatanGui\\GUIDesigns\\GameMenu\\exchange_off.png"

#define GAMEMENU_PLAY_AGAIN_ON "CatanGui\\GUIDesigns\\GameMenu\\play_again_on.png"
#define GAMEMENU_PLAY_AGAIN_OFF "CatanGui\\GUIDesigns\\GameMenu\\play_again_off.png"

#define GAMEMENU_EXIT_ON "CatanGui\\GUIDesigns\\GameMenu\\exit_on.png"
#define GAMEMENU_EXIT_OFF "CatanGui\\GUIDesigns\\GameMenu\\exit_off.png"

#define CONNECT_FOCUS_SOUND "CatanGui\\Sounds\\button_focus.wav"
#define CONNECT_SELECT_SOUND "CatanGui\\Sounds\\press.wav"

GameMenu::
GameMenu(CatanLauncher& _launcher) : WindowUI(1080, 640), launcher(_launcher) {
	///* Creo los componentes */
	//UIComponent* nameBox = UIBuilder::createTextBox("name", 26, TextUI::Mode::LETTER);
	//UIComponent* ipBox = UIBuilder::createTextBox("ip", 26, TextUI::Mode::EVERYTHING);
	//UIComponent* portBox = UIBuilder::createTextBox("port", 25, TextUI::Mode::NUMBER);
	//UIComponent* connectButton = UIBuilder::attachSample(UIBuilder::createButton("connect"));

	///* Configuro los botones! */
	//VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_CONNECT_IDLE);
	//VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_CONNECT_FOCUS);
	//VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_CONNECT_SELECTED);
	//VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_CONNECT_SELECTED);
	//VIEW(connectButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_CONNECT_SELECTED);
	//VIEW(connectButton, 0)->updateModelValues();

	//VIEW(connectButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, CONNECT_SELECT_SOUND);
	//VIEW(connectButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, CONNECT_FOCUS_SOUND);

	///* Configuro los textbox! */
	//VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(nameBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(nameBox, 0)->updateModelValues();

	//VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(ipBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(ipBox, 0)->updateModelValues();

	//VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_TEXTBOX_IDLE);
	//VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(portBox, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_TEXTBOX_SELECTED);
	//VIEW(portBox, 0)->updateModelValues();

	///* Agrego componentes */
	//this->attachComponent(nameBox);
	//this->attachComponent(ipBox);
	//this->attachComponent(portBox);
	//this->attachComponent(connectButton);

	///* Posicion de componentes */
	//MODEL(nameBox, TextUI*)->setPosition(365, 230);
	//MODEL(ipBox, TextUI*)->setPosition(365, 300);
	//MODEL(portBox, TextUI*)->setPosition(365, 370);
	//MODEL(connectButton, MouseUI*)->setPosition(400, 440);

	/* Configuro el background */
	this->setBackground(GAMEMENU_BACKGROUND);
	this->setMusic(GAMEMENU_MUSIC);
}