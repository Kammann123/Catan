#pragma once

#include "../../AllegroUI/WindowUI.h"
#include "../../../CatanGame/Player.h"

/*
* Definicion de posiciones ordenadas dentro de los containers
* de los jugadores y el juego o tablero
*/
#define POSITION_ORE	"ore"
#define POSITION_LUMBER	"lumber"
#define POSITION_BRICK	"brick"
#define POSITION_WOOL	"wool"
#define POSITION_GRAIN	"grain"

#define POSITION_PLAYER_ONE	"player_one"
#define POSITION_PLAYER_TWO	"player_two"

#define POSITION_SETTLEMENT	"settlement"
#define POSITION_ROAD	"road"
#define POSITION_CITY	"city"

#define POSITION_LONGEST_ROAD	"longest_road"

/***************************************
* Identificadores del Container Player *
***************************************/
#define PLAYER_NAME				"name"
#define PLAYER_VICTORY_POINTS	"victory_poitns"
#define PLAYER_ORE				POSITION_ORE
#define PLAYER_LUMBER			POSITION_LUMBER
#define PLAYER_BRICK			POSITION_BRICK
#define PLAYER_WOOL				POSITION_WOOL
#define PLAYER_GRAIN			POSITION_GRAIN
#define PLAYER_SETTLEMENTS		POSITION_SETTLEMENT
#define PLAYER_ROADS			POSITION_ROAD
#define PLAYER_CITY				POSITION_CITY
#define PLAYER_LONGEST_ROAD		POSITION_LONGEST_ROAD

/*******************************************
* Identificadores de los modelos del juego *
*******************************************/
#define PLAYER_ONE_ID	"player_one"
#define PLAYER_TWO_ID	"player_two"
#define LONGEST_ROAD_ID "longest_road_id"
#define ROBBER_ID		"robber"
#define MAP_ID			"map"
#define GAME_ID			"game"

class CatanLauncher;

/*
* GameWindow
* Interfaz grafica del juego Catan.
*/
class GameWindow : public WindowUI {
public:
	/* Constructor */
	GameWindow(CatanLauncher& _launcher);

private:

	/***********************
	* Callbacks y acciones *
	***********************/
	void onDice(void* data);
	void onDicesThrown(void* data);

	/*******************
	* Layouts de la UI *
	*******************/
	void normal_layout(void);

	/****************************************
	* Builder de UIComponentes de GameWindow
	* Nested class.
	****************************************/
	class GameBuilder {
	public:
		static UIComponent* createDice(string id);
		static UIComponent* createPlayer(Player* player);
	};

	CatanLauncher& launcher;
};