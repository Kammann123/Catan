#pragma once

#include "../../AllegroUI/WindowUI.h"

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

#define PLAYER_ONE_ID	"player_one"
#define PLAYER_TWO_ID	"player_two"
#define LONGEST_ROAD_ID "longest_road_id"
#define ROBBER_ID		"robber"
#define MAP_ID		"map"
#define GAME_ID		"game"

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

	/*******************
	* Layouts de la UI *
	*******************/
	void normal_layout(void);

	CatanLauncher& launcher;
};