#include "GameMenu.h"
#include "CatanLauncher.h"
#include "../AllegroWidgets/UIBuilder.h"

#define GAMEMENU_MUSIC		"CatanGui\\Sounds\\catan.ogg"
#define GAMEMENU_BACKGROUND	"CatanGui\\GUIDesigns\\GameMenu\\background.png"


#define GAMEMENU_DISCARD_ON "CatanGui\\GUIDesigns\\GameMenu\\buttons\\discard_on.png"
#define GAMEMENU_DISCARD_OFF "CatanGui\\GUIDesigns\\GameMenu\\buttons\\discard_off.png"

#define GAMEMENU_EXCHANGE_ON "CatanGui\\GUIDesigns\\GameMenu\\buttons\\exchange_on.png"
#define GAMEMENU_EXCHANGE_OFF "CatanGui\\GUIDesigns\\GameMenu\\buttons\\exchange_off.png"

#define GAMEMENU_PLAY_AGAIN_ON "CatanGui\\GUIDesigns\\GameMenu\\buttons\\play_again_on.png"
#define GAMEMENU_PLAY_AGAIN_OFF "CatanGui\\GUIDesigns\\GameMenu\\buttons\\play_again_off.png"

#define GAMEMENU_EXIT_ON "CatanGui\\GUIDesigns\\GameMenu\\buttons\\exit_on.png"
#define GAMEMENU_EXIT_OFF "CatanGui\\GUIDesigns\\GameMenu\\buttons\\exit_off.png"

#define FOCUS_SOUND "CatanGui\\Sounds\\button_focus.wav"
#define SELECT_SOUND "CatanGui\\Sounds\\press.wav"

GameMenu::
GameMenu(CatanLauncher& _launcher) : WindowUI(1080, 640), launcher(_launcher) {
	///* Creo los componentes */
	UIComponent* exitButton = UIBuilder::attachSample(UIBuilder::createButton("exit"));
	UIComponent* discardButton = UIBuilder::attachSample(UIBuilder::createButton("discard"));
	UIComponent* exchangeButton = UIBuilder::attachSample(UIBuilder::createButton("exchange"));
	UIComponent* playAgainButton = UIBuilder::attachSample(UIBuilder::createButton("playAgain"));

	///* Configuro los botones! */
	//Boton de salir
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_EXIT_OFF);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_EXIT_ON);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_EXIT_ON);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_EXIT_OFF);
	VIEW(exitButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_EXIT_ON);
	VIEW(exitButton, 0)->updateModelValues();

	VIEW(exitButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, SELECT_SOUND);
	VIEW(exitButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, FOCUS_SOUND);

	//Boton de descartar cartas
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_DISCARD_OFF);	//HAY QUE PENSAR COMO HACER PARA HABILITARLO DEPENDIENDO DE LA PARTIDA.
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_DISCARD_ON);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_DISCARD_ON);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_DISCARD_OFF);
	VIEW(discardButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_DISCARD_ON);
	VIEW(discardButton, 0)->updateModelValues();

	VIEW(discardButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, SELECT_SOUND);
	VIEW(discardButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, FOCUS_SOUND);

	//Boton de intercambiar cartas
	VIEW(exchangeButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_EXCHANGE_OFF);	//HAY QUE PENSAR COMO HACER PARA HABILITARLO DEPENDIENDO DE LA PARTIDA.
	VIEW(exchangeButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_EXCHANGE_ON);
	VIEW(exchangeButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_EXCHANGE_ON);
	VIEW(exchangeButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_EXCHANGE_OFF);
	VIEW(exchangeButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_EXCHANGE_ON);
	VIEW(exchangeButton, 0)->updateModelValues();

	VIEW(exchangeButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, SELECT_SOUND);
	VIEW(exchangeButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, FOCUS_SOUND);

	//Boton de jugar de nuevo
	VIEW(playAgainButton, 0)->getImages().setConfig(MouseUI::Status::IDLE, GAMEMENU_PLAY_AGAIN_OFF);	//HAY QUE PENSAR COMO HACER PARA HABILITARLO DEPENDIENDO DE LA PARTIDA.
	VIEW(playAgainButton, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEMENU_PLAY_AGAIN_ON);
	VIEW(playAgainButton, 0)->getImages().setConfig(MouseUI::Status::SELECTED, GAMEMENU_PLAY_AGAIN_ON);
	VIEW(playAgainButton, 0)->getImages().setConfig(MouseUI::Status::HOLDING, GAMEMENU_PLAY_AGAIN_OFF);
	VIEW(playAgainButton, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEMENU_PLAY_AGAIN_ON);
	VIEW(playAgainButton, 0)->updateModelValues();

	VIEW(playAgainButton, 1)->getSamples().setConfig(MouseUI::Status::SELECTED, SELECT_SOUND);
	VIEW(playAgainButton, 1)->getSamples().setConfig(MouseUI::Status::FOCUSED, FOCUS_SOUND);

	
	///* Agrego componentes */
	this->attachComponent(exitButton);
	this->attachComponent(discardButton);
	this->attachComponent(exchangeButton);
	this->attachComponent(playAgainButton);

	///* Posicion de componentes */
	MODEL(exitButton, MouseUI*)->setPosition(210, 584);
	MODEL(discardButton, MouseUI*)->setPosition(10, 306);
	MODEL(exchangeButton, MouseUI*)->setPosition(77, 306);
	MODEL(playAgainButton, MouseUI*)->setPosition(142, 306);

	/* Configuro el background */
	this->setBackground(GAMEMENU_BACKGROUND);
	this->setMusic(GAMEMENU_MUSIC);
}