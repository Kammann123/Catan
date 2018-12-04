#include "GameWindow.h"

#include "../../AllegroUI/MouseController.h"
#include "../../AllegroUI/AnimationController.h"
#include "../../AllegroWidgets/UIBuilder.h"
#include "../../../CatanGame/Dice.h"
#include "../CatanLauncher.h"
#include "PlayerView.h"
#include "DiceView.h"

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
	UIComponent* firstDice = GameBuilder::createDice("dice_one");
	UIComponent* secondDice = GameBuilder::createDice("dice_two");
	UIComponent* localPlayer = GameBuilder::createPlayer(launcher.getContext().getGame().getLocalPlayer());

	/******************************
	* Configuracion de player one *
	******************************/
	MODEL(localPlayer, Player*)->setPosition(10, 450);
	MODEL(localPlayer, Player*)->set(PLAYER_NAME, 0, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_VICTORY_POINTS, 160, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_ORE, 0, 90, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_LUMBER, 60, 90, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_BRICK, 120, 90, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_WOOL, 180, 90, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_GRAIN, 240, 90, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_SETTLEMENTS, 0, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_ROADS, 0, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_CITY, 0, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_LONGEST_ROAD, 0, 0, 0);

	/****************************/
	/* Configuracion de botones */
	/****************************/
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_EXIT_NORMAL);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_EXIT_FOCUSED);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_EXIT_SELECTED);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_EXIT_SELECTED);
	(*exitButton)[0]->updateModelValues();

	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_DISCARD_NORMAL);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_DISCARD_FOCUSED);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_DISCARD_SELECTED);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_DISCARD_SELECTED);
	(*discardButton)[0]->updateModelValues();

	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_TRADE_NORMAL);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_TRADE_FOCUSED);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_TRADE_SELECTED);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_TRADE_SELECTED);
	(*tradeButton)[0]->updateModelValues();

	/***********************************
	* Agrego componente a la interfaz  *
	***********************************/
	this->attachComponent(exitButton);
	this->attachComponent(discardButton);
	this->attachComponent(tradeButton);
	this->attachComponent(firstDice);
	this->attachComponent(secondDice);
	this->attachComponent(localPlayer);

	/*********************************
	* Configuro acciones y callbacks *
 	*********************************/
	MODEL(firstDice, Dice*)->setClickAction(bind(&GameWindow::onDice, this, _1));
	MODEL(secondDice, Dice*)->setClickAction(bind(&GameWindow::onDice, this, _1));
	MODEL(firstDice, Dice*)->setLoopEndAction(bind(&GameWindow::onDicesThrown, this, _1));
	MODEL(secondDice, Dice*)->setLoopEndAction(bind(&GameWindow::onDicesThrown, this, _1));

	/**************************************
	* Configuro posiciones de la interfaz *
	**************************************/
	MODEL(exitButton, MouseUI*)->setPosition(63, 240);
	MODEL(discardButton, MouseUI*)->setPosition(63, 190);
	MODEL(tradeButton, MouseUI*)->setPosition(63, 140);
	MODEL(firstDice, Dice*)->setPosition(800, 200);
	MODEL(secondDice, Dice*)->setPosition(850, 200);

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
GameWindow::onDice(void* data) {
	MODEL((*this)["dice_one"], AnimationUI*)->start();
	MODEL((*this)["dice_two"], AnimationUI*)->start();
	(*(*this)["dice_one"])[UIController::Id::MOUSE]->setEnable(false);
	(*(*this)["dice_two"])[UIController::Id::MOUSE]->setEnable(false);
}

void
GameWindow::onDicesThrown(void* data) {
	(*(*this)["dice_one"])[UIController::Id::MOUSE]->setEnable(true);
	(*(*this)["dice_two"])[UIController::Id::MOUSE]->setEnable(true);
}

void
GameWindow::normal_layout(void) {

	/************************
	* Configuro los players *
	************************/
	(*this)[PLAYER_ONE_ID]->getModel()->setVisible(true);

	/************************
	* Configuro los botones *
	************************/
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["exit"]->getModel()->setVisible(true);

	(*this)["discard"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setVisible(true);

	(*this)["trade"]->getModel()->setEnable(true);
	(*this)["trade"]->getModel()->setVisible(true);

	(*this)["dice_one"]->getModel()->setEnable(true);
	(*this)["dice_one"]->getModel()->setVisible(true);

	(*this)["dice_two"]->getModel()->setEnable(true);
	(*this)["dice_two"]->getModel()->setVisible(true);
}

/****************************/
/* Nested Class GameBuilder */
/****************************/

UIComponent*
GameWindow::GameBuilder::createDice(string id) {

	/* Creo primero el modelo */
	UIModel* diceModel = new Dice(id);

	/* Creo el view */
	UIView* diceView = new DiceView((Dice*)diceModel);

	/* Creo el controller */
	UIController* animationController = new AnimationController((AnimationUI*)diceModel);
	UIController* mouseController = new MouseController((MouseUI*)diceModel);

	/* Configuro y hago un attach, luego creo y devuelvo el UIComponent */
	diceModel->attach(diceView);

	UIComponent* dice = new UIComponent(diceModel, { diceView }, { mouseController, animationController });
	return dice;
}

UIComponent*
GameWindow::GameBuilder::createPlayer(Player* player) {

	/* Creo el view */
	UIView* playerView = new PlayerView(player);

	/* Attacheo y luego creo y devuelvo component */
	player->attach(playerView);

	UIComponent* playerComponent = new UIComponent(player, { playerView }, {});
	return playerComponent;
}