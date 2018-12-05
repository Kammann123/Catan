#include "DiscardWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"

#define DISCARD_BACKGROUND "CatanGui\\GUIDesigns\\DiscardWindow\\robbercards_screen_background_v2.png"

#define DISCARD_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_normal.png"
#define DISCARD_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_focus.png"
#define DISCARD_SELECTED "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_selected.png"

#define EXIT_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\exit_normal_v2.png"
#define EXIT_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\exit_selected_v2.png"

#define PLUS_IMG "CatanGui\\GUIDesigns\\DiscardWindow\\plusButton.png"
#define MINUS_IMG "CatanGui\\GUIDesigns\\DiscardWindow\\minusButton.png"

DiscardWindow::
DiscardWindow(string id) : ChildWindowUI(id, 750, 471) {
	UIComponent* discardButton = UIBuilder::createButton("discardButton");
	UIComponent* exitButton = UIBuilder::createButton("exitButton");
	UIComponent* plusWool = UIBuilder::createButton("plusWool");
	UIComponent* minusWool = UIBuilder::createButton("minusWool");
	UIComponent* plusGrain = UIBuilder::createButton("plusGrain");
	UIComponent* minusGrain = UIBuilder::createButton("minusGrain");
	UIComponent* plusBrick = UIBuilder::createButton("plusBrick");
	UIComponent* minusBrick = UIBuilder::createButton("minusBrick");
	UIComponent* plusOre = UIBuilder::createButton("plusOre");
	UIComponent* minusOre = UIBuilder::createButton("minusOre");
	UIComponent* plusLumber = UIBuilder::createButton("plusLumber");
	UIComponent* minusLumber = UIBuilder::createButton("minusLumber");

	/*******************************
	* Configuracion de los botones *
	*******************************/
	(*discardButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, DISCARD_NORMAL);
	(*discardButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, DISCARD_FOCUS);
	(*discardButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, DISCARD_SELECTED);
	(*discardButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, DISCARD_SELECTED);

	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, EXIT_NORMAL);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, EXIT_FOCUS);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, EXIT_FOCUS);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, EXIT_FOCUS);

	(*plusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);
	(*minusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusWool)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	(*plusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);
	(*minusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusGrain)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	(*plusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);
	(*minusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusBrick)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	(*plusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);
	(*minusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusOre)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	(*plusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLUS_IMG);
	(*plusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLUS_IMG);
	(*plusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLUS_IMG);
	(*plusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLUS_IMG);
	(*minusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, MINUS_IMG);
	(*minusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, MINUS_IMG);
	(*minusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, MINUS_IMG);
	(*minusLumber)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, MINUS_IMG);

	/*************************
	* Agrego los componentes *
	*************************/
	this->attachComponent(discardButton);
	this->attachComponent(exitButton);
	this->attachComponent(plusWool);
	this->attachComponent(minusWool);
	this->attachComponent(plusOre);
	this->attachComponent(minusOre);
	this->attachComponent(plusBrick);
	this->attachComponent(minusBrick);
	this->attachComponent(plusLumber);
	this->attachComponent(minusLumber);
	this->attachComponent(plusGrain);
	this->attachComponent(minusGrain);

	/**************************
	* Posicion de componentes *
	**************************/
	MODEL(discardButton, MouseUI*)->setPosition(550, 340);
	MODEL(exitButton, MouseUI*)->setPosition(675, 14);
		
	MODEL(plusWool, MouseUI*)->setPosition(90, 150);
	MODEL(minusWool, MouseUI*)->setPosition(90 + 50, 150);
	MODEL(plusGrain, MouseUI*)->setPosition(90 + 50 + 50, 150);
	MODEL(minusGrain, MouseUI*)->setPosition(90 + 50 + 50 + 50, 150);
	MODEL(plusBrick, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50, 150);
	MODEL(minusBrick, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50 + 50, 150);
	MODEL(plusOre, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50 + 50 + 50, 150);
	MODEL(minusOre, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50 + 50 + 50 + 50, 150);
	MODEL(plusLumber, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50 + 50 + 50 + 50 + 50, 150);
	MODEL(minusLumber, MouseUI*)->setPosition(90 + 50 + 50 + 50 + 50 + 50 + 50 + 50 + 50 + 50, 150);

	/************
	* Callbacks *
	************/
	MODEL(discardButton, MouseUI*)->setClickAction(bind(&DiscardWindow::onDiscard, this, _1));
	MODEL(exitButton, MouseUI*)->setClickAction(bind(&DiscardWindow::onClose, this, _1));

	/****************************
	* Configuraciones generales *
	*****************************/
	this->setBackground(DISCARD_BACKGROUND);

	/*******************
	* Activo el layout *
	*******************/
	this->visibleComponent("discardButton", true);
	this->enableComponent("discardButton", true);
	this->visibleComponent("exitButton", true);
	this->enableComponent("exitButton", true);

	this->visibleComponent("plusWool", true);
	this->enableComponent("plusWool", true);
	this->visibleComponent("minusWool", true);
	this->enableComponent("minusWool", true);

	this->visibleComponent("plusGrain", true);
	this->enableComponent("plusGrain", true);
	this->visibleComponent("minusGrain", true);
	this->enableComponent("minusGrain", true);

	this->visibleComponent("plusBrick", true);
	this->enableComponent("plusBrick", true);
	this->visibleComponent("minusBrick", true);
	this->enableComponent("minusBrick", true);

	this->visibleComponent("plusOre", true);
	this->enableComponent("plusOre", true);
	this->visibleComponent("minusOre", true);
	this->enableComponent("minusOre", true);

	this->visibleComponent("plusLumber", true);
	this->enableComponent("plusLumber", true);
	this->visibleComponent("minusLumber", true);
	this->enableComponent("minusLumber", true);
}

void
DiscardWindow::onClose(void* data) {
	this->setEnable(false);
}

void
DiscardWindow::onDiscard(void* data) {

}