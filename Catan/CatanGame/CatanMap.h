#pragma once

#include "ResourceHex.h"
#include "Building.h"
#include "SeaHex.h"
#include "Player.h"
#include "Robber.h"

#include "../CatanGui/AllegroUI/FrameUI.h"

#include <string>
#include <list>
#include <map>

using namespace std;

class CatanGame;

/*
* position_t - Posiciones vinculadas entre la GUI y las 
* logicas del mapa.
*/
typedef struct {
	double x;
	double y;
	unsigned int info;
} position_t;

/*
* CatanMap 
* Clase CatanMap - Modelizacion del mapa del juego que contiene
* todo aquello que en el se situa, esto es, la tierra, el mar
* y las construcciones realizadas.
*/
class CatanMap : public FrameUI {
public:
	/*
	* CatanMap - Para ser construido necesita unicamente una 
	* referencia al juego.
	*/
	CatanMap(CatanGame* game);
	~CatanMap(void);

	/*************************
	* Generators del mapa
	*************************/
	void generateLand(void);
	void generateSea(void);
	void generateTokens(void);

	/****************************
	* Verifiers de info a cargar 
	****************************/
	bool verifyMap(map<Coord, MapValue> gameMap);
	bool verifyTokens(map<Coord, unsigned char> tokens);

	/*************************
	* Loaders de informacion
	*************************/
	void loadMap(map<Coord, MapValue> gameMap);
	void loadTokens(map<Coord, MapValue> tokens);

	/*************************************
	* Interfaz de construccion en el mapa
	*************************************/
	void build(Building* building, Coord coord);
	void demolish(Building* building);
	list<Building*> buildings(void);

	/************************************
	* Interfaz de utilizacion del robber
	************************************/
	void moveRobber(Coord coord);
	Coord robberPosition(void);

	/************************************
	* Interfaz de informacion del mapa
	************************************/
	list<ResourceHex*> lands(void);
	ResourceHex* land(Coord coord);
	list<SeaHex*> seas(void);
	SeaHex* sea(Coord coord);

	/****************************************************
	* Conexion entre las coordenadas del mapa logicamente
	* y las coordenadas graficamente.
	*****************************************************/
	map<Coord, position_t> screen(void);

private:

	/************************************
	* Rutinas privadas de inicializacion
	* y creacion de objetos internos, asi
	* como de destruccion de los mismos
	************************************/
	void _create_land(void);
	void _create_sea(void);
	void _create_robber(void);

	void _destroy_land(void);
	void _destroy_sea(void);
	void _destroy_robber(void);

	map<Coord, position_t> screenCoords;
	list<ResourceHex*> landMap;
	list<Building*> builtMap;
	list<SeaHex*> seaMap;
	CatanGame * game;
	Robber* robber;
};