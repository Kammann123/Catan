#pragma once

#include "../CatanData/BuildingData.h"

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
	Building(string place, PlayerId player, BuildingType type);
	Building(PlayerId player, BuildingType type);
	Building(BuildingType type);

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
	BuildingType getType(void);

	/*
	* setPlace
	* Define la posicion de la construccion
	*/
	void setPlace(string place);

	/*
	* setPlayer
	* Define a que jugador pertenece 
	*/
	void setPlayer(PlayerId player);

private:
	string place;
	BuildingType type;
	PlayerId player;
};