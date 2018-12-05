#pragma once

#include "MainMenu/MainMenu.h"
#include "GameWindow/GameWindow.h"

/*
* CatanLauncher
* Lanzador del juego de Catan, maneja los diferentes estados 
* y crea la informacion de contexto de los mismo, considerando que
* entre todos se propaga cierta informacion compartida, siendo
* lo que intercambian los objetos.
*/
class CatanLauncher {
public:

	/*
	* States - Estados o etapas del launcher.
	*/
	enum States : unsigned int { MAIN_MENU, GAME_WINDOW, LAUNCHER_CLOSE };

	/* Constructor */
	CatanLauncher();

	/*
	* run - Corre un ciclo del launcher.
	*/
	void run(void);

	/*
	* alive - Determina el si launcher sigue abierto,
	* o si bien, ha finalizado.
	*/
	bool alive(void);

	/*
	* change - Cambia el estado del launcher
	*/
	void change(States newState);

	/*****************************************
	* Interfaz a la informacion del contexto *
	*****************************************/
	void setUsername(string name);
	void setIp(string ip);
	void setPort(unsigned int port);

	string getUsername(void);
	string getIp(void);
	unsigned int getPort(void);

	CatanGame& getGame(void);
	CatanNetworking& getNetworking(void);

private:
	States state;

	GameWindow gamewindow;
	MainMenu mainmenu;

	CatanNetworking networking;
	CatanGame game;

	unsigned int port;
	string username;
	string ip;
};