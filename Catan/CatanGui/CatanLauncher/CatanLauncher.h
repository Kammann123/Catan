#pragma once

#include "CatanContext.h"
#include "MainMenu.h"

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
	enum States : unsigned int { MAIN_MENU, CONNECT_MENU, GAME_WINDOW, LAUNCHER_CLOSE };

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

	/*
	* Acceso a la informacion del contexto
	*/
	CatanContext& getContext(void);

private:
	States state;
	CatanContext context;
	MainMenu mainmenu;
};