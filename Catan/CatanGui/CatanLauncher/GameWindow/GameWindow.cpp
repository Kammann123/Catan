#include "GameWindow.h"

#include "../../AllegroUI/MouseController.h"
#include "../../AllegroUI/AnimationController.h"
#include "../../AllegroWidgets/UIBuilder.h"
#include "../../../CatanGame/Dice.h"
#include "../CatanLauncher.h"

#include "../../AllegroWidgets/ImageView.h"
#include "../../AllegroUI/CounterUI.h"
#include "../../../CatanEvents/BuildingEvent.h"
#include "../../../CatanEvents/RobberCardEvent.h"
#include "../../../CatanEvents/RobberMoveEvent.h"
#include "../../../CatanEvents/DicesEvent.h"
#include "../../../CatanEvents/OfferEvent.h"

#include "../../../CatanGame/CatanStates/RobberCards.h"
#include "../../../CatanGame/CatanStates/FirstBuilds.h"

#include "OfferWindow.h"
#include "DiscardWindow.h"
#include "QuestionWindow.h"
#include "ErrorWindow.h"

#include "PlayerView.h"
#include "RobberView.h"
#include "DiceView.h"
#include "BuildingView.h"
#include "LongestRoadView.h"
#include "CatanMapView.h"

#define GAMEWINDOW_CURSOR			"CatanGui\\Cursor\\cursor_normal.png"
#define GAMEWINDOW_CLICK_CURSOR		"CatanGui\\Cursor\\cursor_clicking.png"
#define GAMEWINDOW_GRAB_CURSOR		"CatanGui\\Cursor\\cursor_grabbing.png"
#define GAMEWINDOW_BUILD_CURSOR		"CatanGui\\Cursor\\cursor_building.png"

#define ICON_IMAGE	"CatanGui\\GUIDesigns\\icon.png"

#define BUILD_CURSOR_ID		10

#define GAMEWINDOW_BACKGROUND "CatanGui\\GUIDesigns\\GameMenu\\background.png"

#define GAMEWINDOW_PASS_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\pass.png"
#define GAMEWINDOW_PASS_FOCUSED		"CatanGui\\GUIDesigns\\GameMenu\\pass_focused.png"
#define GAMEWINDOW_PASS_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\pass_selected.png"

#define GAMEWINDOW_EXIT_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\exit_normal.png"
#define GAMEWINDOW_EXIT_FOCUSED		"CatanGui\\GUIDesigns\\GameMenu\\exit_focused.png"
#define GAMEWINDOW_EXIT_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\exit_selected.png"

#define GAMEWINDOW_DISCARD_NORMAL	"CatanGui\\GUIDesigns\\GameMenu\\discard_normal.png"
#define GAMEWINDOW_DISCARD_FOCUSED	"CatanGui\\GUIDesigns\\GameMenu\\discard_focused.png"
#define GAMEWINDOW_DISCARD_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\discard_selected.png"

#define GAMEWINDOW_TRADE_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\trade_normal.png"
#define GAMEWINDOW_TRADE_FOCUSED	"CatanGui\\GUIDesigns\\GameMenu\\trade_focused.png"
#define GAMEWINDOW_TRADE_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\trade_selected.png"

#define GAMEWINDOW_SIGN_NORMAL	"CatanGui\\GUIDesigns\\GameMenu\\sign.png"
#define GAMEWINDOW_SIGN_FOCUS	"CatanGui\\GUIDesigns\\GameMenu\\sign_focus.png"
#define GAMEWINDOW_COSTS_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\costs.png"

#define PLACING_RADIO		15
#define PLAYER_TWO_OFFSET	25

GameWindow::
GameWindow(CatanLauncher& _launcher) : launcher(_launcher), WindowUI("gameWindow", 1080, 640) {
	UIComponent* passButton = UIBuilder::createButton("pass");
	UIComponent* exitButton = UIBuilder::createButton("exit");
	UIComponent* discardButton = UIBuilder::createButton("discard");
	UIComponent* tradeButton = UIBuilder::createButton("trade");
	UIComponent* firstDice = GameBuilder::createDice("dice_one");
	UIComponent* secondDice = GameBuilder::createDice("dice_two");
	UIComponent* localPlayer = GameBuilder::createPlayer(launcher.getGame().getLocalPlayer());
	UIComponent* remotePlayer = GameBuilder::createPlayer(launcher.getGame().getRemotePlayer());
	UIComponent* robber = GameBuilder::createRobber(launcher.getGame().getCatanMap()->getRobber());
	UIComponent* game = GameBuilder::createCatanGame(&launcher.getGame());
	UIComponent* longestRoad = GameBuilder::createLongestRoad(launcher.getGame().getLongestRoad());
	UIComponent* map = GameBuilder::createMap(launcher.getGame().getCatanMap());
	UIComponent* statusBox = UIBuilder::createInfoBox("status", 30, 140, 12);
	UIComponent* costs = UIBuilder::createToggleImage("costs");

	ChildWindowUI* discardWindow = new DiscardWindow("discardWindow", launcher.getGame());
	ChildWindowUI* offerWindow = new OfferWindow("offerWindow", launcher.getGame());
	ChildWindowUI* gandalf = new QuestionWindow("gandalf");
	ChildWindowUI* error = new ErrorWindow("error", launcher);

	/**********************
	* Configuro Costs Box *
	**********************/
	(*(*costs)["image"])[0]->getImages().setConfig(IV_BITMAP, GAMEWINDOW_COSTS_IMAGE);
	(*(*costs)["button"])[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_SIGN_NORMAL);
	(*(*costs)["button"])[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_SIGN_FOCUS);
	(*(*costs)["button"])[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_SIGN_FOCUS);

	/***********************************
	* Creacion de componentes Building *
	***********************************/
	list<UIComponent*> localBuildings;
	for (Building* building : launcher.getGame().getLocalPlayer()->buildings()) {
		UIComponent* buildingComponent = GameBuilder::createBuilding(building);
		localBuildings.push_back(buildingComponent);
	}
	list<UIComponent*> remoteBuildings;
	for (Building* building : launcher.getGame().getRemotePlayer()->buildings()) {
		UIComponent* buildingComponent = GameBuilder::createRemoteBuilding(building);
		remoteBuildings.push_back(buildingComponent);
	}

	/****************************
	* Configuracion del tablero *
	****************************/
	MODEL(game, CatanGame*)->set(POSITION_LONGEST_ROAD, 875, 10, 0);
	MODEL(map, CatanMap*)->setPosition(180, 20);

	/******************************
	* Configuracion de player one *
	******************************/
	MODEL(localPlayer, Player*)->setPosition(10, 400);
	MODEL(localPlayer, Player*)->set(PLAYER_NAME, 40, 0, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_VICTORY_POINTS, 175, 10, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_ORE, 0, 150, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_LUMBER, 60, 150, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_BRICK, 120, 150, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_GRAIN, 180, 150, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_WOOL, 240, 150, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_SETTLEMENTS, 55, 70, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_ROADS, -20, 75, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_CITY, 130, 70, 0);
	MODEL(localPlayer, Player*)->set(PLAYER_LONGEST_ROAD, 300, 225, 0);

	/******************************
	* Configuracion de player two *
	******************************/
	MODEL(remotePlayer, Player*)->setPosition(775, 400);
	MODEL(remotePlayer, Player*)->set(PLAYER_NAME, 40 + PLAYER_TWO_OFFSET, 0, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_VICTORY_POINTS, 175 + PLAYER_TWO_OFFSET, 10, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_ORE, 0, 150, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_LUMBER, 60, 150, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_BRICK, 120, 150, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_GRAIN, 180, 150, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_WOOL, 240, 150, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_SETTLEMENTS, 55 + PLAYER_TWO_OFFSET, 70, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_ROADS, -20 + PLAYER_TWO_OFFSET, 75, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_CITY, 130 + PLAYER_TWO_OFFSET, 70, 0);
	MODEL(remotePlayer, Player*)->set(PLAYER_LONGEST_ROAD, -60 + PLAYER_TWO_OFFSET, 225, 0);

	/****************************/
	/* Configuracion de botones */
	/****************************/
	(*passButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_PASS_NORMAL);
	(*passButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_PASS_FOCUSED);
	(*passButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_PASS_SELECTED);
	(*passButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_PASS_SELECTED);

	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_EXIT_NORMAL);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_EXIT_FOCUSED);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_EXIT_SELECTED);
	(*exitButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_EXIT_SELECTED);

	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_DISCARD_NORMAL);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_DISCARD_FOCUSED);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_DISCARD_SELECTED);
	(*discardButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_DISCARD_SELECTED);

	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::IDLE, GAMEWINDOW_TRADE_NORMAL);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::FOCUSED, GAMEWINDOW_TRADE_FOCUSED);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::SELECTED, GAMEWINDOW_TRADE_SELECTED);
	(*tradeButton)[0]->getImages().setConfig(MouseUI::Status::DRAGGED, GAMEWINDOW_TRADE_SELECTED);

	/************************
	* Agrego ventanas hijas *
	************************/
	this->attachChild(discardWindow);
	this->attachChild(offerWindow);
	this->attachChild(gandalf);
	this->attachChild(error);

	/***********************************
	* Agrego componente a la interfaz  *
	***********************************/
	this->attachComponent(passButton);
	this->attachComponent(exitButton);
	this->attachComponent(discardButton);
	this->attachComponent(tradeButton);
	this->attachComponent(firstDice);
	this->attachComponent(secondDice);
	this->attachComponent(localPlayer);
	this->attachComponent(remotePlayer);
	this->attachComponent(longestRoad);
	this->attachComponent(game);
	this->attachComponent(map);
	this->attachComponent(robber);
	this->attachComponent(statusBox);
	this->attachComponent(costs);

	/********************************************
	* Agrego componentes Building a la interfaz *
	********************************************/
	for (UIComponent* component : localBuildings) {
		this->attachComponent(component);
		MODEL(component, Building*)->demolish();
	}
	for (UIComponent* component : remoteBuildings) {
		this->attachComponent(component);
		MODEL(component, Building*)->demolish();
	}

	/*********************************
	* Configuro acciones y callbacks *
 	*********************************/
	MODEL(firstDice, Dice*)->setClickAction(bind(&GameWindow::onDice, this, _1));
	MODEL(secondDice, Dice*)->setClickAction(bind(&GameWindow::onDice, this, _1));
	MODEL(firstDice, Dice*)->setLoopEndAction(bind(&GameWindow::onDicesThrown, this, _1));
	MODEL(exitButton, MouseUI*)->setClickAction(bind(&GameWindow::onExit, this, _1));
	MODEL(robber, Robber*)->setDropAction(bind(&GameWindow::onRobberDrop, this, _1));
	MODEL(tradeButton, MouseUI*)->setClickAction(bind(&GameWindow::onTrade, this, _1));
	MODEL(discardButton, MouseUI*)->setClickAction(bind(&GameWindow::onDiscard, this, _1));
	MODEL(passButton, MouseUI*)->setClickAction(bind(&GameWindow::onPass, this, _1));

	/*************************************
	* Configuro acciones de los Building *
	*************************************/
	for (UIComponent* component : localBuildings) {
		MODEL(component, Building*)->setDropAction(bind(&GameWindow::onBuildingDrop, this, _1));
		MODEL(component, Building*)->setMoveAction(bind(&GameWindow::onBuildingMove, this, _1));
	}

	/**************************************
	* Configuro posiciones de la interfaz *
	**************************************/
	MODEL(passButton, MouseUI*)->setPosition(63, 130);
	MODEL(tradeButton, MouseUI*)->setPosition(63, 170);
	MODEL(discardButton, MouseUI*)->setPosition(63, 210);
	MODEL(exitButton, MouseUI*)->setPosition(63, 250);
	MODEL(firstDice, Dice*)->setPosition(730, 20);
	MODEL(secondDice, Dice*)->setPosition(780, 20);
	MODEL(statusBox, UIModelContainer*)->setPosition(860, 180);
	MODEL(costs, UIModelContainer*)->setPosition(805, 0);

	/*************************
	* Posicion de las Childs *
	*************************/
	this->child("discardWindow")->setPosition(150, 70);
	this->child("offerWindow")->setPosition(150, 40);
	this->child("gandalf")->setPosition(95, 40);
	this->child("error")->setPosition(220, 100);

	/***********************************
	* Configuro general de la interfaz *
	***********************************/
	this->setBackground(GAMEWINDOW_BACKGROUND);
	this->setIcon(ICON_IMAGE);
	this->setTitle("Fondue Catan v1.0");
	this->setCursor(GAMEWINDOW_CURSOR);
	this->setClickCursor(GAMEWINDOW_CLICK_CURSOR);
	this->setGrabCursor(GAMEWINDOW_GRAB_CURSOR);
	this->setCloseAction(bind(&GameWindow::onExit, this, _1));
	this->mouse.set(BUILD_CURSOR_ID, GAMEWINDOW_BUILD_CURSOR);

	/************************
	* Configuro los layouts *
	************************/
	this->layouts = {
		{ CatanGame::State::GAME_SYNC, std::bind(&GameWindow::game_sync, this) },
		{ CatanGame::State::FIRST_BUILDS, std::bind(&GameWindow::first_builds, this) },
		{ CatanGame::State::THROW_DICES, std::bind(&GameWindow::throw_dices, this) },
		{ CatanGame::State::ROBBER_CARD, std::bind(&GameWindow::robber_card, this) },
		{ CatanGame::State::ROBBER_MOVE, std::bind(&GameWindow::robber_move, this) },
		{ CatanGame::State::TURN, std::bind(&GameWindow::turn, this) },
		{ CatanGame::State::OFFER_ANSWER, std::bind(&GameWindow::offer_answer, this) },
		{ CatanGame::State::WINNER, std::bind(&GameWindow::winner, this) },
		{ CatanGame::State::GAME_END, std::bind(&GameWindow::game_end, this) },
		{ CatanGame::State::GAME_ERROR, std::bind(&GameWindow::game_error, this) }
	};

	/**************************
	* Activo el layout actual *
	**************************/
	normal_layout();
}

void
GameWindow::updateStatus(void) {
	/* Se despliegan mensajes correspondientes
	*/
	MODEL((*(*this)["status"])["title"], TextUI*)->setText(launcher.getGame().getStateString());
	MODEL((*(*this)["status"])["info"], TextUI*)->setText(launcher.getGame().info());

}

void
GameWindow::update(void) {

	/* Siempre, por las dudas, confirmo recibida la accion
	* del otro jugador para notificar la sincronizacion
	* entre los juegos, seria un "Ok, escuche lo que hizo"
	* pero no a nivel networking, sino para el juego!
	*/
	launcher.getGame().confirm(PlayerId::PLAYER_ONE);

	/* Despliego el layout actual, segun el estado del juego
	* de forma tal que se habilitan aquellas acciones
	* validas al estado actual, y se despliega un mensaje
	* informativo para guiar durante el juego al usuario
	*/
	CatanGame::State currState = launcher.getGame().getState();
	prevState = currState;
	updateStatus();

	/* Se ejecuta el layout del estado actual
	*/
	this->layouts[currState]();

	/* Actualizacion de objetos en funcion de los eventos que se reciben.
	*/
	CatanEvent* event = launcher.getGame().getNextEvent();
	if (event) {
		switch (event->getEvent()) {
			case CatanEvent::Events::THROW_DICES:
				DicesEvent * dices = (DicesEvent*)event;
				MODEL((*this)["dice_one"], Dice*)->setValue(dices->getFirstDice());
				MODEL((*this)["dice_two"], Dice*)->setValue(dices->getSecondDice());
				break;
		}
	}
}

void
GameWindow::onDice(void* data) {
	MODEL((*this)["dice_one"], AnimationUI*)->start();
	MODEL((*this)["dice_two"], AnimationUI*)->start();
	(*(*this)["dice_one"])[UIController::Id::MOUSE]->setEnable(false);
	(*(*this)["dice_two"])[UIController::Id::MOUSE]->setEnable(false);
}

void 
GameWindow::onBuildingMove(void* data) {

	/* Se le pide a Sr.Mouse el controller que tenia
	* agarrado en el proceso de grabbing y de el luego,
	* se obtiene el modelo Building
	*/
	MouseController* controller = mouse.who();
	Building* building = nullptr;
	if (controller) {
		building = (Building*)controller->getModel();
	}

	/* Luego tomo la posicion actual del Building y
	* le pido al mapa del CatanGame que me de todas las coordenadas
	* de logica a mapa en pixeles, busco si en alguna hay coincidencia
	*/
	ALLEGRO_EVENT* event = (ALLEGRO_EVENT*)data;
	position_t mousePosition = { event->mouse.x - MODEL((*this)[MAP_ID], FrameUI*)->xPos(), event->mouse.y - MODEL((*this)[MAP_ID], FrameUI*)->yPos() };
	map<string, position_t> pixels;
	
	/* En funcion del tipo de construccion, elijo que tipo de
	* traductor de coordenadas busco en el CatanMap!
	*/
	switch (building->getType()) {
		case BuildingType::ROAD:
			pixels = launcher.getGame().getCatanMap()->screenEdgeCoords();
			break;
		case BuildingType::CITY: case BuildingType::SETTLEMENT:
			pixels = launcher.getGame().getCatanMap()->screenDotCoords();
			break;
	}

	for (auto pixel : pixels) {
		if (positionDistance(mousePosition, pixel.second) < PLACING_RADIO) {
			this->mouse.force(BUILD_CURSOR_ID);
			return;
		}
	}
	this->mouse.release();
}

void
GameWindow::onDicesThrown(void* data) {

	/* Busco el valor de los dados y pregunto 
	* si son valores validos, ante lo cual ejecuto acciones correspondientes
	*/
	unsigned int fDice = MODEL((*this)["dice_one"], Dice*)->getValue();
	unsigned int sDice = MODEL((*this)["dice_two"], Dice*)->getValue();

	CatanGame& game = launcher.getGame();
	if (game.validDices(fDice, sDice)) {
		game.syncHandle(new DicesEvent(fDice, sDice, PlayerId::PLAYER_ONE));
	}
}

void
GameWindow::onExit(void* data) {
	/* Primero pregunto al usuario si esta seguro de ello, y espero su 
	* respuesta, ante la cual, de ser afirmativo, continuo 
	*/
	bool answer = true;
	
	/* Si acepta, entonces lo que hago es mandar un evento de cierre
	* y el juego directamente aviso a todos los observers y se cierra,
	* de este lado, se cambia el estado del launcher
	*/
	if (answer) {

		/* Evento al handler del game */
		launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::QUIT, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));

		/* Luego finalmente, lo que hago es cambiar de estado */
		launcher.change(CatanLauncher::States::MAIN_MENU);
	}
}

void
GameWindow::onBuildingDrop(void* data) {
	this->mouse.release();

	/* Se le pide a Sr.Mouse el controller que tenia
	* agarrado en el proceso de grabbing y de el luego,
	* se obtiene el modelo Building
	*/
	MouseController* controller = mouse.who();
	Building* building = nullptr;
	if (controller) {
		building = (Building*)controller->getModel();
	}

	/* Luego tomo la posicion actual del Building y 
	* le pido al mapa del CatanGame que me de todas las coordenadas
	* de logica a mapa en pixeles, busco si en alguna hay coincidencia
	*/
	ALLEGRO_EVENT* event = (ALLEGRO_EVENT*)data;
	position_t mousePosition = { event->mouse.x - MODEL((*this)[MAP_ID], FrameUI*)->xPos(), event->mouse.y - MODEL((*this)[MAP_ID], FrameUI*)->yPos() };
	map<string, position_t> pixels;

	/* En funcion del tipo de construccion, elijo que tipo de
	* traductor de coordenadas busco en el CatanMap!
	*/
	switch (building->getType()) {
		case BuildingType::ROAD:
			pixels = launcher.getGame().getCatanMap()->screenEdgeCoords();
			break;
		case BuildingType::CITY: case BuildingType::SETTLEMENT:
			pixels = launcher.getGame().getCatanMap()->screenDotCoords();
			break;
	}

	for (auto pixel : pixels) {
		if (positionDistance(mousePosition, pixel.second) < PLACING_RADIO) {

			/* Se encuentra una ubicacion valida con lo cual,
			* se pregunta si en si misma, la operacion es valida
			* antes de enviarla para no generar errores!
			*/
			CatanGame& game = launcher.getGame();

			/* Fuerzo las coordenadas... */
			Coord coords = pixel.first;
			if (building->getType() == BuildingType::ROAD) {
				coords.forceEdge();
			}
			else {
				coords.forceDot();
			}

			if (game.buildingOk(building->getType(), coords, PlayerId::PLAYER_ONE)) {
				game.syncHandle(new BuildingEvent(coords, building->getType(), PlayerId::PLAYER_ONE));
			}
			else {
				updateStatus();
			}
		}
	}

	/* No se pudo reconocer una ubicacion valida que fuera permitida
	* para realizar la construccion y donde el usuario tuviera las 
	* disponibilidades necesarias, vuelve a casa!
	*/
	building->refactor();
}

void
GameWindow::onRobberDrop(void* data) {
	 
	/* Busco el modelo del robber para determinar su ubicacion actual
	* y buscar una compatibilidad dentro del mapa de pixeles del mapa
	*/
	Robber* robber = launcher.getGame().getCatanMap()->getRobber();
	ALLEGRO_EVENT* event = (ALLEGRO_EVENT*)data;
	position_t robberPosition = { event->mouse.x - MODEL((*this)[MAP_ID], FrameUI*)->xPos(), event->mouse.y - MODEL((*this)[MAP_ID], FrameUI*)->yPos() };

	map<string, position_t> pixels = launcher.getGame().getCatanMap()->screenHexCoords();
	for (auto pixel : pixels) {

		if (positionDistance(robberPosition, pixel.second) < PLACING_RADIO) {

			/* Le mando el evento de cambio de ubicacion al juego
			* para lo cual primero accedo al mismo, obviamente se pregunta si
			* es valido el movimiento antes
			*/
			CatanGame& game = launcher.getGame();

			if (game.validRobberMovement(pixel.first)) {
				game.syncHandle(new RobberMoveEvent(pixel.first, PlayerId::PLAYER_ONE));
			}else{
				updateStatus();
			}
		}
	}


	/* Fue un movimiento equivoco o invalido, volve a casa
	* papa, que aca no tenes nada que hacer
	*/
	robber->refactor();
}

void
GameWindow::onDiscard(void* data) {
	this->child("discardWindow")->setEnable(true);
}

void
GameWindow::onTrade(void* data) {
	this->child("offerWindow")->setEnable(true);
}

void
GameWindow::onPass(void* data) {
	launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::PASS, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));
}

void
GameWindow::acceptOffer(void* data) {
	launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::YES, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));
	this->child("gandalf")->setEnable(false);
}

void
GameWindow::denyOffer(void* data) {
	launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::NO, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));
	this->child("gandalf")->setEnable(false);
}

void
GameWindow::gameOver(void* data) {
	launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::GAME_OVER, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));
	this->child("gandalf")->setEnable(false);
	launcher.change(CatanLauncher::States::MAIN_MENU);
}

void
GameWindow::playAgain(void* data) {
	launcher.getGame().syncHandle(new CatanEvent(CatanEvent::Events::PLAY_AGAIN, CatanEvent::Sources::GUI, PlayerId::PLAYER_ONE));
	this->child("gandalf")->setEnable(false);
}

/**********
* Layouts *
**********/
void 
GameWindow::game_sync(void) {
	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::first_builds(void) {
	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	FirstBuilds* state = (FirstBuilds*)launcher.getGame().getCurrentState();
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			if (launcher.getGame().getTurn() == PlayerId::PLAYER_ONE) {
				if (!MODEL(buildings, Building*)->isBuilt()) {
					if (state->getState() == FirstBuilds::FBStates::BUILD_ROAD && MODEL(buildings, Building*)->getType() == BuildingType::ROAD) {
						buildings->getModel()->setEnable(true);
						continue;
					}
					else if (state->getState() == FirstBuilds::FBStates::BUILD_SETTLEMENT && MODEL(buildings, Building*)->getType() == BuildingType::SETTLEMENT) {
						buildings->getModel()->setEnable(true);
						continue;
					}
				}
			}
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::throw_dices(void){
	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	if (launcher.getGame().getTurn() == PlayerId::PLAYER_ONE) {
		(*this)["dice_one"]->getModel()->setEnable(true);
		(*this)["dice_two"]->getModel()->setEnable(true);
		(*(*this)["dice_one"])[UIController::Id::MOUSE]->setEnable(true);
		(*(*this)["dice_two"])[UIController::Id::MOUSE]->setEnable(true);
	}
	else {
		(*this)["dice_one"]->getModel()->setEnable(false);
		(*this)["dice_two"]->getModel()->setEnable(false);
		(*(*this)["dice_one"])[UIController::Id::MOUSE]->setEnable(false);
		(*(*this)["dice_two"])[UIController::Id::MOUSE]->setEnable(false);
	}
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
}

void
GameWindow::robber_card(void) {
	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	RobberCards* state = (RobberCards*)launcher.getGame().getCurrentState();
	if (state->getPlayerId() == PlayerId::PLAYER_ONE) {
		(*this)["discard"]->getModel()->setEnable(true);
	}
	else {
		(*this)["discard"]->getModel()->setEnable(false);
	}
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::robber_move(void) {
	/**********************
	* Configuro el robber *
	**********************/
	if (launcher.getGame().getTurn() == PlayerId::PLAYER_ONE) {
		(*this)[ROBBER_ID]->getModel()->setEnable(true);
	}
	else {
		(*this)[ROBBER_ID]->getModel()->setEnable(false);
	}

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::turn(void) {
	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			if (!MODEL(buildings, Building*)->isBuilt()) {
				if (launcher.getGame().getTurn() == PlayerId::PLAYER_ONE) {
					buildings->getModel()->setEnable(true);
					continue;
				}
			}
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	if (launcher.getGame().getTurn() == PlayerId::PLAYER_ONE) {
		(*this)["pass"]->getModel()->setEnable(true);
		(*this)["trade"]->getModel()->setEnable(true);
	}
	else {
		(*this)["pass"]->getModel()->setEnable(false);
		(*this)["trade"]->getModel()->setEnable(false);
	}
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::offer_answer(void) {

	/**************************
	* Gandalf! Venite papa... *
	**************************/
	/* Verifico que no este abierto ya... se puede llamar
	* varias veces al update, no deberia ejecutarse esto
	* mas que la primera vez!
	*/
	if (!this->child("gandalf")->isEnabled()) {
		if (launcher.getGame().getTurn() == PlayerId::PLAYER_TWO) {
			/* Busco el evento del juego */
			OfferEvent* offer = (OfferEvent*)launcher.getGame().getNextEvent();

			/* Le doy formato a la propuesta! */
			string msg = launcher.getGame().getRemotePlayer()->getName() + " quiere hacer un intercambio.\n";

			list<ResourceId>& givenCards = offer->getGiven();
			unsigned int woolGiven = count(givenCards.begin(), givenCards.end(), ResourceId::PASTURES);
			unsigned int grainGiven = count(givenCards.begin(), givenCards.end(), ResourceId::FIELD);
			unsigned int brickGiven = count(givenCards.begin(), givenCards.end(), ResourceId::HILL);
			unsigned int oreGiven = count(givenCards.begin(), givenCards.end(), ResourceId::MOUNTAIN);
			unsigned int lumberGiven = count(givenCards.begin(), givenCards.end(), ResourceId::FOREST);

			list<ResourceId>& recvCards = offer->getRecv();
			unsigned int woolRecv = count(recvCards.begin(), recvCards.end(), ResourceId::PASTURES);
			unsigned int grainRecv = count(recvCards.begin(), recvCards.end(), ResourceId::FIELD);
			unsigned int brickRecv = count(recvCards.begin(), recvCards.end(), ResourceId::HILL);
			unsigned int oreRecv = count(recvCards.begin(), recvCards.end(), ResourceId::MOUNTAIN);
			unsigned int lumberRecv = count(recvCards.begin(), recvCards.end(), ResourceId::FOREST);

			if (woolGiven) {
				msg += "Ofrece " + to_string(woolGiven) + " lana/s.\n";
			}
			if (grainGiven) {
				msg += "Ofrece " + to_string(grainGiven) + " trigo/s.\n";
			}
			if (brickGiven) {
				msg += "Ofrece " + to_string(brickGiven) + " ladrillo/s.\n";
			}
			if (oreGiven) {
				msg += "Ofrece " + to_string(oreGiven) + " piedra/s.\n";
			}
			if (lumberGiven) {
				msg += "Ofrece " + to_string(lumberGiven) + " madera/s.\n";
			}

			if (woolRecv) {
				msg += "Pide " + to_string(woolRecv) + " lana/s.\n";
			}
			if (grainRecv) {
				msg += "Pide " + to_string(grainRecv) + " trigo/s.\n";
			}
			if (brickRecv) {
				msg += "Pide " + to_string(brickRecv) + " ladrillo/s.\n";
			}
			if (oreRecv) {
				msg += "Pide " + to_string(oreRecv) + " piedra/s.\n";
			}
			if (lumberRecv) {
				msg += "Pide " + to_string(lumberRecv) + " madera/s.\n";
			}

			/* Hago aparecer la ventana de gandalf */
			((QuestionWindow*)this->child("gandalf"))->question(msg, bind(&GameWindow::acceptOffer, this, _1), bind(&GameWindow::denyOffer, this, _1));
		}
	}

	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::winner(void) {

	/********************
	* Gandalf!!! Veni!! *
	********************/
	/* Verifico que no haya venido aun gandalf...
	* porque solo se debe llamar a la ventana la primera vez!!!
	*/
	if (!this->child("gandalf")->isEnabled()) {
		if (launcher.getGame().getWinner() == PlayerId::PLAYER_TWO) {
			/* Hago aparecer la ventana de gandalf */
			((QuestionWindow*)this->child("gandalf"))->question("Has perdido esta batalla, no te rindas Gran Hobbit. Deseas jugar de nuevo?", bind(&GameWindow::playAgain, this, _1), bind(&GameWindow::gameOver, this, _1));
		}
	}

	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::game_end(void) {
	/* Cierro el juego. Por lo menos interfaz... */
	launcher.change(CatanLauncher::States::MAIN_MENU);
}

void
GameWindow::game_error() {

	/* Ventana de error! */
	if (!this->child("error")->isEnabled()) {
		this->child("error")->setEnable(true);
	}

	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(false);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		if (MODEL(buildings, Building*)->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			buildings->getModel()->setEnable(false);
		}
	}

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(false);
	(*this)["exit"]->getModel()->setEnable(true);
	(*this)["discard"]->getModel()->setEnable(false);
	(*this)["trade"]->getModel()->setEnable(false);
	(*this)["dice_one"]->getModel()->setEnable(false);
	(*this)["dice_two"]->getModel()->setEnable(false);
}

void
GameWindow::normal_layout(void) {

	/********************
	* Configuro el mapa *
	********************/
	(*this)[MAP_ID]->getModel()->setEnable(true);
	(*this)[MAP_ID]->getModel()->setVisible(true);

	/****************************
	* Configuro el longest road *
	****************************/
	(*this)[LONGEST_ROAD_ID]->getModel()->setEnable(true);
	(*this)[LONGEST_ROAD_ID]->getModel()->setVisible(true);

	/**********************
	* Configuro el robber *
	**********************/
	(*this)[ROBBER_ID]->getModel()->setEnable(true);
	(*this)[ROBBER_ID]->getModel()->setVisible(true);

	/**************************
	* Configuro los buildings *
	**************************/
	for (UIComponent* buildings : (*this)(BUILDING_ID)) {
		buildings->getModel()->setVisible(true);
		buildings->getModel()->setEnable(true);
	}

	/************************
	* Configuro los players *
	************************/
	(*this)[PLAYER_ONE_ID]->getModel()->setVisible(true);
	(*this)[PLAYER_TWO_ID]->getModel()->setVisible(true);

	/************************
	* Configuro los botones *
	************************/
	(*this)["pass"]->getModel()->setEnable(true);
	(*this)["pass"]->getModel()->setVisible(true);
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
	(*this)["costs"]->getModel()->setEnable(true);
	(*this)["status"]->getModel()->setEnable(true);
	(*this)["status"]->getModel()->setVisible(true);
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

UIComponent*
GameWindow::GameBuilder::createBuilding(Building* building) {

	/* Creo el view */
	UIView* buildingView = new BuildingView(building);

	/* Creo los controllers */
	UIController* mouseController = new MouseController(building);

	/* Attacheo y creo/devuelvo el componente */
	building->attach(buildingView);

	UIComponent* buildingComponent = new UIComponent(building, { buildingView }, { mouseController });
	return buildingComponent;
}

UIComponent*
GameWindow::GameBuilder::createRemoteBuilding(Building* building) {

	/* Creo el view */
	UIView* buildingView = new BuildingView(building);;

	/* Attacheo y creo/devuelvo el componente */
	building->attach(buildingView);

	UIComponent* buildingComponent = new UIComponent(building, { buildingView }, { });
	return buildingComponent;
}

UIComponent* 
GameWindow::GameBuilder::createRobber(Robber* robber) {

	/* Creo el view */
	UIView* robberView = new RobberView(robber);

	/* Creo el controller */
	UIController* robberController = new MouseController(robber);

	/* Attach y creacion del component */
	robber->attach(robberView);

	UIComponent* robberComponent = new UIComponent(robber, { robberView }, { robberController });
	return robberComponent;
}

UIComponent* 
GameWindow::GameBuilder::createLongestRoad(LongestRoad* longestRoad) {

	/* Creo el view */
	UIView* longestView = new LongestRoadView(longestRoad);

	/* Attacheo y doy component*/
	longestRoad->attach(longestView);

	UIComponent* longestRoadComponent = new UIComponent(longestRoad, { longestView }, {});
	return longestRoadComponent;
}

UIComponent* 
GameWindow::GameBuilder::createCatanGame(CatanGame* game) {
	return new UIComponent(game, {}, {});
}

UIComponent* 
GameWindow::GameBuilder::createMap(CatanMap* map) {

	/* Creo el view */
	UIView * mapView = new CatanMapView(map);

	/* Attach y creo componentes */
	map->attach(mapView);

	UIComponent* mapComponent = new UIComponent(map, { mapView }, {});
	return mapComponent;
}