#include "DiscardWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"

#define DISCARD_BACKGROUND "CatanGui\\GUIDesigns\\DiscardWindow\\robbercards_screen_background_v2.png"

#define DISCARD_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_normal.png"
#define DISCARD_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_focus.png"
#define DISCARD_SELECTED "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_selected.png"

#define EXIT_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\exit_normal_v2.png"
#define EXIT_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\exit_selected_v2.png"

DiscardWindow::
DiscardWindow(string id) : ChildWindowUI(id, 750, 471) {
	UIComponent* discardButton = UIBuilder::createButton("discardButton");
	UIComponent* exitButton = UIBuilder::createButton("exitButton");
	UIComponent* wool = UIBuilder::createCounter("wool", 9);
	UIComponent* grain = UIBuilder::createCounter("grain", 9);
	UIComponent* brick = UIBuilder::createCounter("brick", 9);
	UIComponent* ore = UIBuilder::createCounter("ore", 9);
	UIComponent* lumber = UIBuilder::createCounter("lumber", 9);

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

	/*************************
	* Agrego los componentes *
	*************************/
	this->attachComponent(discardButton);
	this->attachComponent(exitButton);
	this->attachComponent(wool);
	this->attachComponent(ore);
	this->attachComponent(grain);
	this->attachComponent(lumber);
	this->attachComponent(brick);

	/**************************
	* Posicion de componentes *
	**************************/
	MODEL(discardButton, MouseUI*)->setPosition(550, 340);
	MODEL(exitButton, MouseUI*)->setPosition(675, 14);

	MODEL(wool, CounterUI*)->setPosition(105, 140);
	MODEL(grain, CounterUI*)->setPosition(100 + 120, 140);
	MODEL(brick, CounterUI*)->setPosition(100 + 120 * 2, 140);
	MODEL(ore, CounterUI*)->setPosition(100 + 120 * 3, 140);
	MODEL(lumber, CounterUI*)->setPosition(100 + 120 * 4, 140);

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
	this->visibleComponent("wool", true);
	this->enableComponent("wool", true);
	this->visibleComponent("grain", true);
	this->enableComponent("grain", true);
	this->visibleComponent("brick", true);
	this->enableComponent("brick", true);
	this->visibleComponent("ore", true);
	this->enableComponent("ore", true);
	this->visibleComponent("lumber", true);
	this->enableComponent("lumber", true);
}

void
DiscardWindow::onClose(void* data) {
	this->setEnable(false);
}

void
DiscardWindow::onDiscard(void* data) {

}