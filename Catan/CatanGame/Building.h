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
	void build(Coord coord, double x, double y);
	void demolish(Coord coord, double x, double y);

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

	/*
	* getNeighbours
	* Devuelve la lista de vecinos, para ir visitandolos a cada
	* uno de ellos y llevar la cuenta de las visitas
	*/
	list<Building*> getNeighbours(void);

	/*
	* hasNeighbours
	* Devuelve true si el building tiene vecinos agregados
	*/
	bool hasNeighbours(void);

	/*
	* wasVisited
	* Consulta si ya fue visitada la construccion en particular
	*/
	bool wasVisited(void);

	/*
	* visit
	* Marca el estado de la visita en esta construccion
	*/
	void visit(bool status = true);

private:
	list<Building*> neighbours;
	BuildingType type;
	Player* player;
	Coord coord;

	bool built;
	bool visited;
};