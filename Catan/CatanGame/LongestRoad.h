#pragma once

#include "../CatanGui/AllegroUI/FrameUI.h"
#include "Player.h"

class CatanGame;

#define LONGEST_ROAD_POINTS	2

/*
* LongestRoad 
* Clase modelo con la informacion de quien
* posee el longest road, y la informacion
* para su representacion grafica
*/
class LongestRoad : public FrameUI {
public:

	/*
	* LongestRoad - Se construye inicialmente
	* sin mas informacion que una referencia al juego
	* para conocer la ubicacion de su posicion defecto
	*/
	LongestRoad(CatanGame* game);

	/*
	* assign - Se asigna la carta a un jugador
	* y en dicho proceso se cambia su ubicacion.
	* 
	* Por defecto nullptr indica que se remueve.
	*/
	void assign(Player* player = nullptr);

	/*
	* who - Permite conocer a quien pertenece
	*/
	PlayerId who(void) const;

	/* Definicion del refactor para el modelo */
	void refactor(void);

private:
	Player * player;
	CatanGame* game;
};