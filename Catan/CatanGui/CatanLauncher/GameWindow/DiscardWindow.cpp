#include "DiscardWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"
#include "../../AllegroUI/CounterUI.h"
#include "../../../CatanEvents/RobberCardEvent.h"
#include "../../AllegroWidgets/MultiLabelView.h"

#define DISCARD_BACKGROUND "CatanGui\\GUIDesigns\\DiscardWindow\\robbercards_screen_background_v2.png"

#define DISCARD_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_normal.png"
#define DISCARD_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_focus.png"
#define DISCARD_SELECTED "CatanGui\\GUIDesigns\\DiscardWindow\\discard_button_selected.png"

#define EXIT_NORMAL "CatanGui\\GUIDesigns\\DiscardWindow\\exit_normal_v2.png"
#define EXIT_FOCUS "CatanGui\\GUIDesigns\\DiscardWindow\\exit_selected_v2.png"

DiscardWindow::
DiscardWindow(string id, CatanGame& _game) : ChildWindowUI(id, 750, 471), game(_game) {
	UIComponent* discardButton = UIBuilder::createButton("discardButton");
	UIComponent* exitButton = UIBuilder::createButton("exitButton");
	UIComponent* wool = UIBuilder::createCounterBox("wool", 9);
	UIComponent* grain = UIBuilder::createCounterBox("grain", 9);
	UIComponent* brick = UIBuilder::createCounterBox("brick", 9);
	UIComponent* ore = UIBuilder::createCounterBox("ore", 9);
	UIComponent* lumber = UIBuilder::createCounterBox("lumber", 9);
	UIComponent* label = UIBuilder::createMultiLabel("status", 600, 15);

	/**************************
	* Configuracion del label *
	**************************/
	(*label)[0]->getColors().setConfig(MLA_TEXT_COLOR, 200, 150, 150);

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
	this->attachComponent(label);

	/**************************
	* Posicion de componentes *
	**************************/
	MODEL(discardButton, MouseUI*)->setPosition(550, 340);
	MODEL(exitButton, MouseUI*)->setPosition(675, 14);

	MODEL(wool, UIModelContainer*)->setPosition(80, 140);
	MODEL(grain, UIModelContainer*)->setPosition(75 + 120, 140);
	MODEL(brick, UIModelContainer*)->setPosition(75 + 120 * 2, 140);
	MODEL(ore, UIModelContainer*)->setPosition(75 + 120 * 3, 140);
	MODEL(lumber, UIModelContainer*)->setPosition(75 + 120 * 4, 140);
	MODEL(label, TextUI*)->setPosition(100, 300);

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
	this->visibleComponent("status", true);
	this->enableComponent("status", true);
}

void
DiscardWindow::onClose(void* data) {
	this->setEnable(false);
}

void
DiscardWindow::onDiscard(void* data) {
	/* Busco las cantidades de recursos seleccionadas por
	* el jugador. Buscando los models counters
	*/
	unsigned int woolCount = MODEL((*(*this)["wool"])["counter"], CounterUI*)->getValue();
	unsigned int grainCount = MODEL((*(*this)["grain"])["counter"], CounterUI*)->getValue();
	unsigned int brickCount = MODEL((*(*this)["brick"])["counter"], CounterUI*)->getValue();
	unsigned int oreCount = MODEL((*(*this)["ore"])["counter"], CounterUI*)->getValue();
	unsigned int lumberCount = MODEL((*(*this)["lumber"])["counter"], CounterUI*)->getValue();

	/* Valido la accion, en funcion de lo cual, notifico un error, o bien
	* ejecuto la accion. En caso de ejecutar la accion, cierro la ventana
	*/
	list<ResourceId> cards = game.generateCards(woolCount, grainCount, brickCount, oreCount, lumberCount);
	if (game.validateRobberCards(cards, PlayerId::PLAYER_ONE)) {
		game.syncHandle(new RobberCardEvent(cards, PlayerId::PLAYER_ONE));
		this->setEnable(false);
	}
	else {
		MODEL((*this)["status"], TextUI*)->setText( game.info() );
	}
}