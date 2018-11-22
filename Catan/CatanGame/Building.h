#pragma once

enum PlayerId;

/*
* BuildingType
* Tipos de construcciones del juego
*/
enum BuildingType : unsigned int { SETTLEMENT, ROAD, CITY };

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
	Building(PlayerId player, BuildingType type);

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

private:
	string place;
	BuildingType type;
	PlayerId player;
};