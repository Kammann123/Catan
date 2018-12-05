#include "OfferWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"

#define TRADE_BACKGROUND "CatanGui\\GUIDesigns\\OfferWindow\\exchange_screen_background_v2.png"

#define TRADE_NORMAL "CatanGui\\GUIDesigns\\OfferWindow\\trade_button_normal.png"
#define TRADE_FOCUS "CatanGui\\GUIDesigns\\OfferWindow\\trade_button_focused.png"
#define TRADE_SELECTED "CatanGui\\GUIDesigns\\OfferWindow\\trade_button_selected.png"

#define EXIT_NORMAL "CatanGui\\GUIDesigns\\OfferWindow\\exit_normal_v2.png"
#define EXIT_FOCUS "CatanGui\\GUIDesigns\\OfferWindow\\exit_selected_v2.png"

#define DOCK_NORMAL "CatanGui\\GUIDesigns\\OfferWindow\\dock.png"
#define DOCK_FOCUS "CatanGui\\GUIDesigns\\OfferWindow\\dock_focus.png"
#define DOCK_SELECTED "CatanGui\\GUIDesigns\\OfferWindow\\dock_selected.png"

#define PLAYER_NORMAL "CatanGui\\GUIDesigns\\OfferWindow\\player.png"
#define PLAYER_FOCUS "CatanGui\\GUIDesigns\\OfferWindow\\player_focus.png"
#define PLAYER_SELECTED "CatanGui\\GUIDesigns\\OfferWindow\\player_selected.png"

#define BANK_NORMAL "CatanGui\\GUIDesigns\\OfferWindow\\bank.png"
#define BANK_FOCUS "CatanGui\\GUIDesigns\\OfferWindow\\bank_focus.png"
#define BANK_SELECTED "CatanGui\\GUIDesigns\\OfferWindow\\bank_selected.png"

OfferWindow::
OfferWindow(string id) : ChildWindowUI(id, 750, 700) {
	UIComponent* tradeButton = UIBuilder::createButton("tradeButton");
	UIComponent* exitButton = UIBuilder::createButton("exitButton");
	UIComponent* wantedWool = UIBuilder::createCounter("wantedWool", 9);
	UIComponent* wantedGrain = UIBuilder::createCounter("wantedGrain", 9);
	UIComponent* wantedBrick = UIBuilder::createCounter("wantedBrick", 9);
	UIComponent* wantedOre = UIBuilder::createCounter("wantedOre", 9);
	UIComponent* wantedLumber = UIBuilder::createCounter("wantedLumber", 9);
	UIComponent* givenWool = UIBuilder::createCounter("givenWool", 9);
	UIComponent* givenGrain = UIBuilder::createCounter("givenGrain", 9);
	UIComponent* givenBrick = UIBuilder::createCounter("givenBrick", 9);
	UIComponent* givenOre = UIBuilder::createCounter("givenOre", 9);
	UIComponent* givenLumber = UIBuilder::createCounter("givenLumber", 9);

	UIComponent* bank = UIBuilder::createButton("bank");
	UIComponent* dock = UIBuilder::createButton("dock");
	UIComponent* player = UIBuilder::createButton("player");

	/*******************************
	* Configuracion de los botones *
	*******************************/
	(*tradeButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, TRADE_NORMAL);
	(*tradeButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, TRADE_FOCUS);
	(*tradeButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, TRADE_SELECTED);
	(*tradeButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, TRADE_SELECTED);

	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, EXIT_NORMAL);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, EXIT_FOCUS);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, EXIT_FOCUS);
	(*exitButton)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, EXIT_FOCUS);

	(*dock)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, DOCK_NORMAL);
	(*dock)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, DOCK_FOCUS);
	(*dock)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, DOCK_SELECTED);
	(*dock)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, DOCK_SELECTED);
	(*dock)[0]->getImages().setConfig((unsigned int)MouseUI::Status::HOLDING, DOCK_SELECTED);

	(*player)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, PLAYER_NORMAL);
	(*player)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, PLAYER_FOCUS);
	(*player)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, PLAYER_SELECTED);
	(*player)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, PLAYER_SELECTED);
	(*player)[0]->getImages().setConfig((unsigned int)MouseUI::Status::HOLDING, PLAYER_SELECTED);

	(*bank)[0]->getImages().setConfig((unsigned int)MouseUI::Status::IDLE, BANK_NORMAL);
	(*bank)[0]->getImages().setConfig((unsigned int)MouseUI::Status::FOCUSED, BANK_FOCUS);
	(*bank)[0]->getImages().setConfig((unsigned int)MouseUI::Status::SELECTED, BANK_SELECTED);
	(*bank)[0]->getImages().setConfig((unsigned int)MouseUI::Status::DRAGGED, BANK_SELECTED);
	(*bank)[0]->getImages().setConfig((unsigned int)MouseUI::Status::HOLDING, BANK_SELECTED);

	MODEL(bank, MouseUI*)->setEnableHold(true);
	MODEL(player, MouseUI*)->setEnableHold(true);
	MODEL(dock, MouseUI*)->setEnableHold(true);

	/*************************
	* Agrego los componentes *
	*************************/
	this->attachComponent(tradeButton);
	this->attachComponent(exitButton);
	this->attachComponent(wantedWool);
	this->attachComponent(wantedOre);
	this->attachComponent(wantedGrain);
	this->attachComponent(wantedLumber);
	this->attachComponent(wantedBrick);
	this->attachComponent(givenWool);
	this->attachComponent(givenOre);
	this->attachComponent(givenGrain);
	this->attachComponent(givenLumber);
	this->attachComponent(givenBrick);
	this->attachComponent(bank);
	this->attachComponent(dock);
	this->attachComponent(player);

	/**************************
	* Posicion de componentes *
	**************************/
	MODEL(tradeButton, MouseUI*)->setPosition(550, 340);
	MODEL(exitButton, MouseUI*)->setPosition(675, 14);

	MODEL(wantedWool, CounterUI*)->setPosition(105, 125);
	MODEL(wantedGrain, CounterUI*)->setPosition(100 + 125, 125);
	MODEL(wantedBrick, CounterUI*)->setPosition(100 + 125 * 2, 125);
	MODEL(wantedOre, CounterUI*)->setPosition(100 + 125 * 3, 125);
	MODEL(wantedLumber, CounterUI*)->setPosition(100 + 125 * 4, 125);

	MODEL(givenWool, CounterUI*)->setPosition(105, 285);
	MODEL(givenGrain, CounterUI*)->setPosition(100 + 125, 285);
	MODEL(givenBrick, CounterUI*)->setPosition(100 + 125 * 2, 285);
	MODEL(givenOre, CounterUI*)->setPosition(100 + 125 * 3, 285);
	MODEL(givenLumber, CounterUI*)->setPosition(100 + 125 * 4, 285);

	MODEL(bank, MouseUI*)->setPosition(300, 450);
	MODEL(dock, MouseUI*)->setPosition(50, 465);
	MODEL(player, MouseUI*)->setPosition(550, 475);

	/************
	* Callbacks *
	************/
	MODEL(tradeButton, MouseUI*)->setClickAction(bind(&OfferWindow::onTrade, this, _1));
	MODEL(exitButton, MouseUI*)->setClickAction(bind(&OfferWindow::onClose, this, _1));

	/****************************
	* Configuraciones generales *
	*****************************/
	this->setBackground(TRADE_BACKGROUND);

	/*******************
	* Activo el layout *
	*******************/
	this->visibleComponent("tradeButton", true);
	this->enableComponent("tradeButton", true);
	this->visibleComponent("exitButton", true);
	this->enableComponent("exitButton", true);
	this->visibleComponent("wantedWool", true);
	this->enableComponent("wantedWool", true);
	this->visibleComponent("wantedGrain", true);
	this->enableComponent("wantedGrain", true);
	this->visibleComponent("wantedBrick", true);
	this->enableComponent("wantedBrick", true);
	this->visibleComponent("wantedOre", true);
	this->enableComponent("wantedOre", true);
	this->visibleComponent("wantedLumber", true);
	this->enableComponent("wantedLumber", true);
	this->visibleComponent("givenWool", true);
	this->enableComponent("givenWool", true);
	this->visibleComponent("givenGrain", true);
	this->enableComponent("givenGrain", true);
	this->visibleComponent("givenBrick", true);
	this->enableComponent("givenBrick", true);
	this->visibleComponent("givenOre", true);
	this->enableComponent("givenOre", true);
	this->visibleComponent("givenLumber", true);
	this->enableComponent("givenLumber", true);
	this->visibleComponent("dock", true);
	this->enableComponent("dock", true);
	this->visibleComponent("player", true);
	this->enableComponent("player", true);
	this->visibleComponent("bank", true);
	this->enableComponent("bank", true);
}

void
OfferWindow::onClose(void* data) {
	this->setEnable(false);
}

void
OfferWindow::onTrade(void* data) {

}