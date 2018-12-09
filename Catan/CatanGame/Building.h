#pragma once

#include "../CatanGui/AllegroUI/MouseUI.h"
#include "../CatanData/BuildingData.h"
#include "Coord.h"

#include <string>
#include <list>

using namespace std;

class Player;

/*
* Building
* Clase de construccion del juego, con el tipo, posicion o ubicacion,
* y usuario a quien pertenece.
*/
class Building : public MouseUI {
public:

	/*
	* Building - Unicamente puede ser construido por un player
	* indicando a quien pertenece y que tipo de building es.
	*/
	Building(Player* player, BuildingType type);

	/* Definicion del metodo refactor */
	void refactor(void);

	/*
	* getters - Permiten leer o acceder a la informacion
	* del building.
	*/
	bool isBuilt(void);
	Coord getPlace(void);
	Player* getPlayer(void);
	BuildingType getType(void);

	/*
	* Build y Demolish - Construccion y demolicion
	* del building, cambian la coordenada, posicion,
	* y estado del building.
	*/
	void build(Coord coord, double x, double y, double radian);
	void demolish(void);

	/****************************************************
	* Metodos para la modelizacion de un building como 
	* un nodo o vertice de grafos, y su recorrido en el
	* mismo para poder determinar longest road.
	****************************************************/

	/*
	* addNeighbour/removeNeighbour
	* Agrego/Quito un vecino contiguo a la construccion, para ir armando
	* las conexiones del grafo de caminos y construcciones
	*/
	void addNeighbour(list<Building*> buildings);
	void addNeighbour(Building* building);
	void removeNeighbour(Building* building);
	void removeNeighbour(void);

	list<Building*> getNeighbours(void);
	void visit(bool status = true);
	bool hasNeighbours(void);
	bool wasVisited(void);
	bool isHead(void);

private:

	/* isBuildingSide - Se busca determinar si el building pertenece
	* al lado conjunto por los demas buildings en la lista, para clasificar
	* los lados de un road.
	*/
	bool isBuildingSide(list<Building*> side, Building* building);

	list<Building*> neighbours;
	BuildingType type;
	Player* player;
	Coord coord;

	bool visited;
	bool built;
};