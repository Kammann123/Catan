#include "OfferWindow.h"
#include "../../AllegroWidgets/UIBuilder.h"
#include "../../AllegroWidgets/MultiLabelView.h"

#include "../../../CatanEvents/BankEvent.h"
#include "../../../CatanEvents/OfferEvent.h"

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
OfferWindow(string id, CatanGame& _game) : ChildWindowUI(id, 750, 700), game(_game) {
	UIComponent* tradeButton = UIBuilder::createButton("tradeButton");
	UIComponent* exitButton = UIBuilder::createButton("exitButton");
	UIComponent* wantedWool = UIBuilder::createCounterBox("wantedWool", 9);
	UIComponent* wantedGrain = UIBuilder::createCounterBox("wantedGrain", 9);
	UIComponent* wantedBrick = UIBuilder::createCounterBox("wantedBrick", 9);
	UIComponent* wantedOre = UIBuilder::createCounterBox("wantedOre", 9);
	UIComponent* wantedLumber = UIBuilder::createCounterBox("wantedLumber", 9);
	UIComponent* givenWool = UIBuilder::createCounterBox("givenWool", 9);
	UIComponent* givenGrain = UIBuilder::createCounterBox("givenGrain", 9);
	UIComponent* givenBrick = UIBuilder::createCounterBox("givenBrick", 9);
	UIComponent* givenOre = UIBuilder::createCounterBox("givenOre", 9);
	UIComponent* givenLumber = UIBuilder::createCounterBox("givenLumber", 9);
	UIComponent* label = UIBuilder::createMultiLabel("status", 600, 15);

	/**************************
	* Configuracion del label *
	**************************/
	(*label)[0]->getColors().setConfig(MLA_TEXT_COLOR, 200, 150, 150);

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
	this->attachComponent(label);

	/**************************
	* Posicion de componentes *
	**************************/
	MODEL(tradeButton, MouseUI*)->setPosition(550, 340);
	MODEL(exitButton, MouseUI*)->setPosition(675, 14);

	MODEL(wantedWool, UIModelContainer*)->setPosition(80, 125);
	MODEL(wantedGrain, UIModelContainer*)->setPosition(75 + 120, 125);
	MODEL(wantedBrick, UIModelContainer*)->setPosition(75 + 120 * 2, 125);
	MODEL(wantedOre, UIModelContainer*)->setPosition(75 + 120 * 3, 125);
	MODEL(wantedLumber, UIModelContainer*)->setPosition(75 + 120 * 4, 125);

	MODEL(givenWool, UIModelContainer*)->setPosition(80, 285);
	MODEL(givenGrain, UIModelContainer*)->setPosition(75 + 120, 285);
	MODEL(givenBrick, UIModelContainer*)->setPosition(75 + 120 * 2, 285);
	MODEL(givenOre, UIModelContainer*)->setPosition(75 + 120 * 3, 285);
	MODEL(givenLumber, UIModelContainer*)->setPosition(75 + 120 * 4, 285);

	MODEL(bank, MouseUI*)->setPosition(300, 450);
	MODEL(dock, MouseUI*)->setPosition(50, 465);
	MODEL(player, MouseUI*)->setPosition(550, 475);
	MODEL(label, TextUI*)->setPosition(100, 315);

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
	this->visibleComponent("status", true);
	this->enableComponent("status", true);
}

void
OfferWindow::onClose(void* data) {
	this->setEnable(false);
}

void
OfferWindow::onTrade(void* data) {
	/* Busco las cantidades de recursos seleccionadas por
	* el jugador. Buscando los models counters
	*/
	unsigned int woolGiven = MODEL((*(*this)["givenWool"])["counter"], CounterUI*)->getValue();
	unsigned int grainGiven = MODEL((*(*this)["givenGrain"])["counter"], CounterUI*)->getValue();
	unsigned int brickGiven = MODEL((*(*this)["givenBrick"])["counter"], CounterUI*)->getValue();
	unsigned int oreGiven = MODEL((*(*this)["givenOre"])["counter"], CounterUI*)->getValue();
	unsigned int lumberGiven = MODEL((*(*this)["givenLumber"])["counter"], CounterUI*)->getValue();

	unsigned int woolWanted = MODEL((*(*this)["wantedWool"])["counter"], CounterUI*)->getValue();
	unsigned int grainWanted = MODEL((*(*this)["wantedGrain"])["counter"], CounterUI*)->getValue();
	unsigned int brickWanted = MODEL((*(*this)["wantedBrick"])["counter"], CounterUI*)->getValue();
	unsigned int oreWanted = MODEL((*(*this)["wantedOre"])["counter"], CounterUI*)->getValue();
	unsigned int lumberWanted = MODEL((*(*this)["wantedLumber"])["counter"], CounterUI*)->getValue();

	/* Valido la accion, en funcion de lo cual, notifico un error, o bien
	* ejecuto la accion. En caso de ejecutar la accion, cierro la ventana
	*/
	list<ResourceId> givenCards = game.generateCards(woolGiven, grainGiven, brickGiven, oreGiven, lumberGiven);
	list<ResourceId> wantedCards = game.generateCards(woolWanted, grainWanted, brickWanted, oreWanted, lumberWanted);
	if (MODEL((*this)["bank"], MouseUI*)->getStatus() == MouseUI::Status::HOLDING) {
		if (game.isValidBankExchange(givenCards, wantedCards, PlayerId::PLAYER_ONE)) {
			game.syncHandle(new BankEvent(givenCards, wantedCards, PlayerId::PLAYER_ONE));
			this->setEnable(false);
		}
		else {
			MODEL((*this)["status"], TextUI*)->setText(game.info());
		}
	}
	else if (MODEL((*this)["dock"], MouseUI*)->getStatus() == MouseUI::Status::HOLDING) {
		if (game.isValidDockExchange(givenCards, wantedCards, PlayerId::PLAYER_ONE)) {
			game.syncHandle(new BankEvent(givenCards, wantedCards, PlayerId::PLAYER_ONE));
			this->setEnable(false);
		}
		else {
			MODEL((*this)["status"], TextUI*)->setText(game.info());
		}
	}
	else if (MODEL((*this)["player"], MouseUI*)->getStatus() == MouseUI::Status::HOLDING) {
		if (game.isValidPlayerExchange(givenCards, wantedCards, PlayerId::PLAYER_ONE)) {
			game.syncHandle(new OfferEvent(givenCards, wantedCards, PlayerId::PLAYER_ONE));
			this->setEnable(false);
		}
		else {
			MODEL((*this)["status"], TextUI*)->setText(game.info());
		}
	}
}