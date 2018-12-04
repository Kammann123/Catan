#pragma once

#include "ResourceHex.h"
#include "Building.h"
#include "SeaHex.h"
#include "Player.h"
#include "Robber.h"

#include "../CatanData/MapData.h"

#include "../CatanGui/AllegroUI/FrameUI.h"

#include <string>
#include <list>
#include <map>

using namespace std;

class CatanGame;

/* Map assignments */
#define HILL_HEX_COUNT		3
#define FOREST_HEX_COUNT	4
#define	MOUNTAIN_HEX_COUNT	3
#define FIELD_HEX_COUNT		4
#define PASTURE_HEX_COUNT	4
#define DESERT_HEX_COUNT	1

/*
* position_t - Posiciones vinculadas entre la GUI y las 
* logicas del mapa.
*/
typedef struct {
	double x;
	double y;
	double info;
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
	void loadTokens(map<Coord, unsigned char> tokens);

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
	Robber* getRobber(void);

	/************************************
	* Interfaz de informacion del mapa
	************************************/
	map<Coord, MapValue> getMap(void);
	map<Coord, unsigned char> getTokens(void);
	list<ResourceHex*> lands(void);
	ResourceHex* land(Coord coord);
	list<SeaHex*> seas(void);
	SeaHex* sea(Coord coord);

	/****************************************************
	* Conexion entre las coordenadas del mapa logicamente
	* y las coordenadas graficamente.
	*****************************************************/
	map<string, position_t> screen(void);

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

	/***************************************************
	* Configuracion hardcode de las ubicaciones en
	* pantalla de las coordenadas logicas del juego
	***************************************************/
	void _init_coords(void);

	map<string, position_t> screenCoords;
	list<ResourceHex*> landMap;
	list<Building*> builtMap;
	list<SeaHex*> seaMap;
	CatanGame * game;
	Robber* robber;
};