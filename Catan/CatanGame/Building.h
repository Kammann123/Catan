#pragma once

#include "../CatanData/BuildingData.h"
#include "Coord.h"

#include <string>

using namespace std;

#define BUILDING_NOT_PLACED	"FFF"

enum class PlayerId;

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
	Building(Coord place, PlayerId player, BuildingType type);
	Building(PlayerId player, BuildingType type);
	Building(BuildingType type);

	/*
	* getPlace()
	* Devuelve las coordenadas de la construcción
	*/
	Coord getPlace(void);

	/*
	* getPlayer
	* Devuelve el jugador al que pertence la construccion
	*/
	PlayerId getPlayer(void);

	/*
	* getType
	* Devuelve el tipo de onstruccion
	*/
	BuildingType getType(void);

	/*
	* setPlace
	* Define la posicion de la construccion
	*/
	void setPlace(Coord place);

	/*
	* setPlayer
	* Define a que jugador pertenece 
	*/
	void setPlayer(PlayerId player);

private:
	Coord place;
	BuildingType type;
	PlayerId player;
};