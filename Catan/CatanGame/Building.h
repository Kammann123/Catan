#pragma once

#include "Player.h"

/*
* BuildingType
* Tipos de construcciones del juego
*/
enum BuldingType { SETTLEMENT, ROAD, CITY };

/*
* Building
* Clase de construccion del juego, con el tipo, posicion o ubicacion,
* y usuario a quien pertenece.
*/
class Building {
public:
	/*
	* Constructor
	*/
	Building(PlayerId player, BuldingType type);

	/*
	* getPlace()
	* Devuelve las coordenadas de la construcción
	*/
	string getPlace(void);

	/*
	* getPlayer
	* Devuelve el jugador al que pertence la construccion
	*/
	PlayerId getPlayer(void);

	/*
	* getType
	* Devuelve el tipo de onstruccion
	*/
	BuldingType getType(void);

	/*
	* setPlace
	* Define la posicion de la construccion
	*/
	void setPlace(string place);

private:
	string place;
	BuldingType type;
	PlayerId player;

};